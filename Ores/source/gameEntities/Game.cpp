#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "Brick.h"

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow)
{
	InitGame();
	m_textureManager = std::make_unique<TextureManager>(m_window.get());
	InitGameObjects();
}

void Game::InitGame()
{
	if (SDL_Init(SDL_INIT_VIDEO) != -1)
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
										Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, SDL_WINDOW_SHOWN));
	}
	else
	{
		printf("%s", SDL_GetError());
	}
}
void Game::InitGameObjects()
{
	m_go = std::make_unique<Brick>();
	m_go2 = std::make_unique<Brick>(150, 150);
}

void Game::Draw()
{
	m_textureManager->ClearRender();
	m_go->Draw();
	m_go2->Draw();
	m_textureManager->PresentRender();
}

void Game::Update()
{
	m_go->Update();
	m_go2->Update();
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

