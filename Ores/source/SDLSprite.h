#pragma once
#include <memory>
#include "ISprite.h"

struct SDL_Texture;
void SDL_DestroyTexture(SDL_Texture* s);

class SDLSprite : public ISprite
{
public:
	SDLSprite();
	
	void Draw() const;
	void LoadSprite(const char* spritePath);
private:
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;
};