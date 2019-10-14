#include "pch.h"

#include "TextureManager.h"
#include "Enums.h"
#include "Constants.h"
#include "Brick.h"

std::map<BrickColor, std::shared_ptr<SDL_Texture>> TextureManager::m_BrickColorToTexture;
std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> TextureManager::m_renderer{ nullptr, SDL_DestroyRenderer };
SDL_Rect TextureManager::m_rect;

TextureManager::TextureManager(SDL_Window* window)
{
	CreateRenderer(window);
	LoadTexture(Consts::imagePath, BrickColor::Blue);
}

void TextureManager::ClearRender() const
{
	SDL_RenderClear(m_renderer.get());
}

void TextureManager::PresentRender() const
{
	SDL_RenderPresent(m_renderer.get());
}

void TextureManager::Draw(const Brick* brickToDraw)
{	
	SDL_RenderCopy(m_renderer.get(), m_BrickColorToTexture[brickToDraw->GetColor()].get(), NULL, &brickToDraw->GetTransform().Rect());
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

void TextureManager::LoadTexture(const char* texturePath, BrickColor color)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface{ IMG_Load(texturePath), SDL_FreeSurface };
	
	if (m_surface != nullptr)
	{
		AddSpriteToMapOfSprites(color, std::move(m_surface));
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
	m_BrickColorToTexture.try_emplace(color, std::move(texture));
}

TextureManager::~TextureManager()
{
	printf("texture manager deleted\n");
}

