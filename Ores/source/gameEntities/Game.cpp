#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"
#include "DirectionToVector.h"
#include "MatrixGrid.h"
#include "EventsHandler.h"
#include "ParticleSystemManager.h"
#include "TimerWithFillBar.h"

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow),
	 m_grid(std::make_unique<MatrixGrid>()),
	m_eventsHandler(std::make_unique<EventsHandler>()),
	m_ColumnSpawnTimer(std::make_unique<TimerWithFillBar>())
{
	CreateWindow();
	TextureManager::InitTextureManager(m_window.get());
	InitGame();
}

void Game::InitGame()
{
	m_grid->Init();
	InitGameObjects();
	m_ColumnSpawnTimer->Clear();
	InitTimer(Consts::SEC_BETWEEN_COLUMN_SPAWNS);
	ParticleSystemManager::Init();
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

// TODO functions in this block should be moved to a class of their own******************
void Game::InitTimer(float secondsBetweenColumnsSpawns)
{
	m_currentSecondsBetweenColumnsSpawns = secondsBetweenColumnsSpawns;
	m_ColumnSpawnTimer->Init(m_currentSecondsBetweenColumnsSpawns, PushSpawnColumnEvent);
}

void Game::ChangeSecondsBetweenColumnSpawns()
{
	m_currentSecondsBetweenColumnsSpawns = GetNextColumnSpawnTimer();
	m_ColumnSpawnTimer->ChangeSecondsBetweenCalls(m_currentSecondsBetweenColumnsSpawns);
}

float Game::GetNextColumnSpawnTimer() const
{
	return std::max(
		m_currentSecondsBetweenColumnsSpawns - Consts::DECREMENT_COLUMN_SPAWN_TIMER_SECS,
		Consts::MIN_SEC_BETWEEN_COLUMN_SPAWNS
	);
}
//***************************************************************************************
void Game::Draw()	
{
	TextureManager::ClearRender();
	m_warningArea.Draw();
	m_grid->Draw();
	dynamic_cast<TimerWithFillBar*>(m_ColumnSpawnTimer.get())->GetUIBar()->Draw();	// TODO substitute this with array of UI elements
	ParticleSystemManager::Draw();
	TextureManager::PresentRender();
}

void Game::Update() 
{
	ParticleSystemManager::Update();
	dynamic_cast<TimerWithFillBar*>(m_ColumnSpawnTimer.get())->GetUIBar()->Update();	// TODO substitute this with array of UI elements
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