#include "pch.h"
#include "TextureManager.h"

TextureManager::TextureManager(SDL_Window* window)
	:m_renderer(nullptr, SDL_DestroyRenderer)
{
	CreateRenderer(window);
}

void TextureManager::ClearRender() const
{
	SDL_RenderClear(m_renderer.get());
}

void TextureManager::PresentRender() const
{
	SDL_RenderPresent(m_renderer.get());
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
		//m_textures.emplace_back(m_surface);
	}
	else
	{
		printf("Image %s not loaded. SDL_ERROR: %s", texturePath, SDL_GetError());
	}
}

void TextureManager::ApplyTexture()
{/*
	m_textureToDelete.reset(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()));
	if (m_textureToDelete == nullptr)
	{
		printf("Texture %s not loaded, SDL_ERROR: %s", spritePath, SDL_GetError());
	}*/
}

TextureManager::~TextureManager()
{
	printf("texture manager deleted\n");
}

