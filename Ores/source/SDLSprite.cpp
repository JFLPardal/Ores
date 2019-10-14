#include "pch.h"

#include "SDLSprite.h"
#include "Game.h"

SDLSprite::SDLSprite()
	:m_texture(nullptr, SDL_DestroyTexture)
{
}

SDLSprite::SDLSprite(std::string& spritePath)
	:m_texture(TextureManager::GetSprite(spritePath), SDL_DestroyTexture)
{
}

void SDLSprite::Draw() const
{
	TextureManager::Draw(m_texture.get());
}

void SDLSprite::SetSprite(std::string spritePath)
{
	printf("set sprite\n");
	m_texture.reset(TextureManager::GetSprite(spritePath));
}

SDLSprite::~SDLSprite()
{
	printf("SDLSprite deleted\n");
}

