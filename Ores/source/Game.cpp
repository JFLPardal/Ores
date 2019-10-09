#include "Game.h"

#include "Constants.h"

Game::Game()
{
	Init();
}

void Game::Init()
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_surface{ nullptr, SDL_FreeSurface };
	if (SDL_Init(SDL_INIT_VIDEO) != -1)
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
										Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, SDL_WINDOW_SHOWN));
		if (m_window != nullptr)
		{
			m_surface.reset(SDL_GetWindowSurface(m_window.get()));
			SDL_FillRect(m_surface.get(), NULL, SDL_MapRGBA(m_surface->format, 0, 0, 110, 125));
			SDL_UpdateWindowSurface(m_window.get());
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
}

void Game::Draw()
{
	
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

void Game::Clean()
{
	SDL_Quit();
}

