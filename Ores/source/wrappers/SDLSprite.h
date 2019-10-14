#pragma once
#include "ISprite.h"

struct SDL_Texture;
void SDL_DestroyTexture(SDL_Texture* s);

class SDLSprite //: public ISprite
{/*
public:
	SDLSprite();
	SDLSprite(std::string& spritePath);
	~SDLSprite();
	
	void Draw() const override;
	void SetSprite(std::string spritePath) override;
private:
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;*/
};