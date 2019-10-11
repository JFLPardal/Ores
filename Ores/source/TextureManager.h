#pragma once

struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;

class TextureManager
{
public:
	TextureManager(SDL_Window* window);
	~TextureManager();
	
	void ClearRender() const;
	void PresentRender()const;
	void LoadTexture(const char* texturePath);
	void ApplyTexture();
private:
	void CreateRenderer(SDL_Window* window);
	//std::vector<std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> m_textures; //	TODO change to unique_ptr
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};