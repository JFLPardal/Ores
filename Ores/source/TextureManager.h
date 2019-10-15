#pragma once

#include "Enums.h"
#include <map>

struct SDL_Window;
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

class Brick;

void SDL_DestroyTexture(SDL_Texture*);
void SDL_DestroyRenderer(SDL_Renderer*);
void SDL_FreeSurface(SDL_Surface*);

class TextureManager
{
public:
	TextureManager(SDL_Window* window);
	~TextureManager();
	
	void ClearRender() const;
	void PresentRender()const;
	static void Draw(const Brick* objectToDraw);

	SDL_Renderer* GetRenderer() { return m_renderer.get(); }
private:
	void CreateRenderer(SDL_Window* window);
	void LoadTexture(const char* texturePath, BrickColor color);
	void AddSpriteToMapOfSprites(const BrickColor color, std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface);
private:
	static std::map<BrickColor, std::shared_ptr<SDL_Texture>> m_BrickColorToTexture;
	static std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
	static SDL_Rect m_rect;
};