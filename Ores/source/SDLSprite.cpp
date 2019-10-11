#include "pch.h"

#include "SDLSprite.h"

SDLSprite::SDLSprite()
	:m_texture(nullptr, SDL_DestroyTexture)
{
	
}

void SDLSprite::Draw() const
{
	// SDL_RenderCopy(m_renderer.get(), m_texture.get(), NULL, sd);
}

void SDLSprite::LoadSprite(const char* spritePath)
{
	
}
