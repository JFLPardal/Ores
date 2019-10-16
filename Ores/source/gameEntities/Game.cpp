#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow)
{
	m_bricks.resize(Consts::NUM_MAX_COLUMNS);
	for(auto& column : m_bricks)
	{
		column.reserve(Consts::BRICKS_PER_COLUMN);
	}
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
	InitBricks();
}

void Game::InitBricks()
{
	uint x = Consts::INITIAL_BRICK_X;
	uint y = Consts::INITIAL_BRICK_Y;
	uint xInc = Consts::BRICK_W;
	uint yInc = Consts::BRICK_H;
	
	for(size_t column = 0; column < Consts::NUM_MAX_COLUMNS; column++)
	{
		for(size_t row = 0; row < Consts::BRICKS_PER_COLUMN; row++)
		{
			m_bricks[column].emplace_back(std::make_unique<Brick>(x, y)); // construct brick on the vertex with these params (saves copies)
			y += yInc;
		}
		y = Consts::INITIAL_BRICK_Y;
		x -= xInc;
	}
}

void Game::Draw()	// TODO refactor for
{
	m_textureManager->ClearRender();
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			brick->Draw();
		}
	}
	m_textureManager->PresentRender();
}

void Game::Update() // TODO refactor for
{
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			brick->Update();
		}
	}
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
			printf("button click: x: %d y: %d\n", event->button.x, event->button.y);
			if(IsBrickOnClickedPosition(event->button.x, event->button.y))
			{
				// process click
				printf("cliked on a brick %d , %d ,%d\n", m_clickedBrick.GetTransform().X(), m_clickedBrick.GetTransform().Y(), m_clickedBrick.GetColor());
			}
		}
	}
}

bool Game::IsBrickOnClickedPosition(int x, int y)
{
	SDL_Point positionClicked{x, y};
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			if (SDL_PointInRect(&positionClicked, &brick->GetTransform().Rect()))
			{
				m_clickedBrick = *brick;
				return true;
			}
		}
	}
	return false;
}

void Game::Clean()
{
	SDL_Quit();
}

Game::~Game()
{
	Clean();
}