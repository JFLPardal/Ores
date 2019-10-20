#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"
#include "DirectionToVector.h"
#include "MatrixGrid.h"
#include "EventsHandler.h"

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow),
	 m_grid(std::make_unique<MatrixGrid>()),
	m_eventsHandler(std::make_unique<EventsHandler>())
{
	CreateWindow();
	TextureManager::InitTextureManager(m_window.get());
	InitGame();
}

void Game::InitGame()
{
	m_grid->Init();
	InitGameObjects();
	m_eventsHandler->InitTimer();
}

void Game::CreateWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != -1)
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
	m_warningArea = GameObject(Consts::LOSING_WARNING_X, Consts::LOSING_WARNING_Y, Consts::LOSING_WARNING_W, Consts::LOSING_WARNING_H);
	m_grid->InitBricks();
}


void Game::Draw()	
{
	TextureManager::ClearRender();
	m_warningArea.Draw();
	m_grid->Draw();
	TextureManager::PresentRender();
}

void Game::Update() 
{
	m_grid->Update();
}

void Game::ProcessEvents()
{
	m_eventsHandler->ProcessEvents(*this);
}

Game::~Game()
{
	SDL_Quit();
}