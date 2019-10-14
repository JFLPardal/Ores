#include "pch.h"
#include "TextureManager.h"
#include "Constants.h"

std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> TextureManager::m_renderer{ nullptr, SDL_DestroyRenderer };
std::map<std::string, std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> TextureManager::m_filePathToTexture{};

TextureManager::TextureManager(SDL_Window* window)
	//:m_renderer(nullptr, SDL_DestroyRenderer)
{
	CreateRenderer(window);
	LoadTexture(Consts::imagePath);
}

void TextureManager::ClearRender() const
{
	SDL_RenderClear(m_renderer.get());
}

void TextureManager::PresentRender() const
{
	SDL_RenderPresent(m_renderer.get());
}

void TextureManager::Draw(SDL_Texture* spriteToDraw)
{
	SDL_RenderCopy(m_renderer.get(), spriteToDraw, NULL, NULL);
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
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface{ IMG_Load(texturePath), SDL_FreeSurface };
	
	if (m_surface != nullptr)
	{
		AddSpriteToMapOfSprites(texturePath, std::move(m_surface));
	}
	else
	{
		printf("Image %s not loaded. SDL_ERROR: %s", texturePath, SDL_GetError());
	}
}

SDL_Texture* TextureManager::GetSprite(std::string& spritePath)	// TODO this argument is pretty bad for comparisons...
{
	auto entry = m_filePathToTexture.find(spritePath);
	return entry->second.get();
}


void TextureManager::ApplyTexture()
{/*
	m_textureToDelete.reset(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()));
	if (m_textureToDelete == nullptr)
	{
		printf("Texture %s not loaded, SDL_ERROR: %s", spritePath, SDL_GetError());
	}*/
}

void TextureManager::AddSpriteToMapOfSprites(const char* texturePath, std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface)
{
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture
	(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()),
		SDL_DestroyTexture);
	m_filePathToTexture.try_emplace(texturePath, std::move(texture));
}

TextureManager::~TextureManager()
{
	printf("texture manager deleted\n");
}
