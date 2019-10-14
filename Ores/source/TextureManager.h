#pragma once

struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;

void SDL_DestroyTexture(SDL_Texture*);

class TextureManager
{
public:
	TextureManager(SDL_Window* window);
	~TextureManager();
	
	void ClearRender() const;
	void PresentRender()const;
	static void Draw(SDL_Texture* spriteToDraw);
	
	void LoadTexture(const char* texturePath);
	static SDL_Texture* GetSprite(std::string& spritePath);
	void ApplyTexture();

	auto GetRenderer() { return m_renderer.get(); }
private:
	void CreateRenderer(SDL_Window* window);
	void AddSpriteToMapOfSprites(const char* texturePath,
	                             std::unique_ptr<SDL_Surface, void(*)(SDL_Surface* surface)> m_surface);
private:
	static std::map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> m_filePathToTexture;
	static std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};