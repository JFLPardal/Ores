#include "pch.h"

#include "TextureManager.h"
#include "Enums.h"
#include "Constants.h"
#include "Brick.h"
#include "Particle.h"
#include "Bar.h"

std::map<BrickColor, std::shared_ptr<SDL_Texture>> TextureManager::m_brickColorToTexture;
std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> TextureManager::m_renderer{ nullptr, SDL_DestroyRenderer };
std::shared_ptr<SDL_Texture> TextureManager::m_particleTexture;

//SDL_Rect TextureManager::m_rect;

void TextureManager::InitTextureManager(SDL_Window* window)
{
	CreateRenderer(window);
	LoadTexture(Consts::blueOre, BrickColor::Blue);
	LoadTexture(Consts::redOre, BrickColor::Red);
	LoadTexture(Consts::greenOre, BrickColor::Green);
	LoadTexture(Consts::greyOre, BrickColor::Grey);
	LoadTexture(Consts::yellowOre, BrickColor::Yellow);
	LoadTexture(Consts::brickParticle);
}


void TextureManager::ClearRender() 
{
	SDL_RenderClear(m_renderer.get());
}

void TextureManager::PresentRender() 
{
	SDL_RenderPresent(m_renderer.get());
}

void TextureManager::Draw(const Brick* brickToDraw)
{	
	SDL_RenderCopy(m_renderer.get(), m_brickColorToTexture[brickToDraw->GetColor()].get(), NULL, &brickToDraw->GetTransform().Rect());
}

void TextureManager::Draw(const GameObject* objectToDraw)
{
	SDL_RenderCopy(m_renderer.get(), m_brickColorToTexture[Red].get(), NULL, &objectToDraw->GetTransform().Rect());
}

void TextureManager::Draw(const Particle* objectToDraw)
{
	SDL_RenderCopy(m_renderer.get(), m_particleTexture.get(), NULL, &objectToDraw->GetTransform().Rect());
}

void TextureManager::Draw(const Bar* objectToDraw)
{
	SDL_RenderCopy(m_renderer.get(), m_brickColorToTexture[Grey].get(), NULL, &objectToDraw->GetTransform().Rect());
}

void TextureManager::CreateRenderer(SDL_Window* window)
{
	m_renderer.reset(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
	if (m_renderer == nullptr)
	{
		printf("Renderer not created. SDL_ERROR: %s", SDL_GetError());
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 110, 125);
	}
}

void TextureManager::LoadTexture(const char* texturePath)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{ IMG_Load(texturePath), SDL_FreeSurface };
	if (surface != nullptr)
	{
		std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture
											(SDL_CreateTextureFromSurface(m_renderer.get(), surface.get()),
											SDL_DestroyTexture);
		m_particleTexture = std::move(texture);
	}
	else
	{
		printf("Image %s not loaded. SDL_ERROR: %s", texturePath, SDL_GetError());
	}
}

void TextureManager::LoadTexture(const char* texturePath, BrickColor color)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{ IMG_Load(texturePath), SDL_FreeSurface };
	
	if (surface != nullptr)
	{
		AddSpriteToMapOfSprites(color, std::move(surface));
	}
	else
	{
		printf("Image %s not loaded. SDL_ERROR: %s", texturePath, SDL_GetError());
	}
}

void TextureManager::AddSpriteToMapOfSprites(const BrickColor color, std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface)
{
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture
									(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()),
										SDL_DestroyTexture);
	m_brickColorToTexture.try_emplace(color, std::move(texture));
}

