#include "Game.h"

#include "Constants.h"

Game::Game()
	: m_window(nullptr, SDL_DestroyWindow), m_textureToDelete(nullptr, SDL_DestroyTexture)
	, m_renderer(nullptr, SDL_DestroyRenderer)
{
	Init();
}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != -1)
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
										Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, SDL_WINDOW_SHOWN));
		if (m_window != nullptr)
		{
			CreateRenderer();
		}
		else
		{
			printf("%s", SDL_GetError());
		}
	}
	else
	{
		printf("%s", SDL_GetError());
	}
	// texture loading 
	const char* imagePath = "../Ores/assets/sprites/paddle.png";
	LoadTexture(imagePath);
}

void Game::Draw()
{
	SDL_RenderClear(m_renderer.get());
	SDL_Rect* sd = new SDL_Rect;
	sd->w = 128;
	sd->h = 45;
	sd->x = 100;
	sd->y = 100;
	SDL_RenderCopy(m_renderer.get(), m_textureToDelete.get(), NULL, sd);
	SDL_RenderPresent(m_renderer.get());
}

void Game::Update()
{
	
}

void Game::ProcessEvents()
{
	auto event = std::make_unique<SDL_Event>();
	while(SDL_PollEvent(event.get()) != 0)
	{
		if(event->type == SDL_QUIT)
		{
			m_isRunning = false;
		}
	}
}

void Game::CreateRenderer()
{
	m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED));
	if (m_renderer == nullptr)
	{
		printf("Renderer not created. SDL_ERROR: %s", SDL_GetError());
	}
	else
	{
		SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 110, 125);
	}
}

void Game::LoadTexture(const char* spritePath)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface{ IMG_Load(spritePath), SDL_FreeSurface };
	//m_surface.reset(IMG_Load(spritePath));
	if (m_surface == nullptr)
	{
		printf("Image %s not loaded. SDL_ERROR: %s", spritePath, SDL_GetError());
	}
	m_textureToDelete.reset(SDL_CreateTextureFromSurface(m_renderer.get(), m_surface.get()));
	if (m_textureToDelete == nullptr)
	{
		printf("Texture %s not loaded, SDL_ERROR: %s", spritePath, SDL_GetError());
	}
}

void Game::Clean()
{
	SDL_Quit();
}

