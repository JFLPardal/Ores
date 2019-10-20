#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"
#include "DirectionToVector.h"
#include "MatrixGrid.h"

Uint32 PushSpawnColumnEvent(Uint32 msBetweenSpawns, void* params)	// TODO MOVE THIS SOMEWHERE ELSE
{
	SDL_UserEvent userEvent;
	userEvent.type = SDL_USEREVENT;
	userEvent.code = UserEvent::SpawnColumn;

	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user = userEvent;

	SDL_PushEvent(&event);
	return msBetweenSpawns;
}

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow),
	 m_grid(std::make_unique<MatrixGrid>())
{
	CreateWindow();
	TextureManager::InitTextureManager(m_window.get());
	InitGame();
}

void Game::InitGame()
{
	m_grid->Init();
	InitGameObjects();
	InitTimer();
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

void Game::InitTimer()
{
	int s;
	m_spawnNewColumnTimer = SDL_AddTimer(Consts::MS_BETWEEN_COLUMN_SPAWNS, PushSpawnColumnEvent, &s);
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
	auto event = std::make_unique<SDL_Event>();
	while(SDL_PollEvent(event.get()) != 0)
	{
		if(event->type == SDL_QUIT)
		{
			m_isRunning = false;
		}
		else if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
		{
			if(m_grid->IsBrickOnClickedPosition(event->button.x, event->button.y, m_clickedBrick))
			{
				std::set<std::pair<uint, uint>> indexesToDelete;
				m_grid->FindSequenceStartingIn(m_clickedBrick, indexesToDelete);
				if(indexesToDelete.size() > 1)
				{
					m_grid->DeleteSequence(indexesToDelete);
					m_grid->DeleteEmptyColumns();
					m_grid->UpdatePositionOfBricks();
				}
			}
		}
		if(event->type == SDL_USEREVENT && event->user.code == UserEvent::SpawnColumn)
		{
			if(m_grid->CurrentNumberOfColumns() < Consts::NUM_MAX_COLUMNS)
			{
				m_grid->SpawnColumn();
			}
			else
			{
				SDL_RemoveTimer(m_spawnNewColumnTimer);
				m_grid->ClearGrid();
				InitGame();
			}
			m_grid->UpdatePositionOfBricks();
		}
	}
}

Game::~Game()
{
	SDL_Quit();
}