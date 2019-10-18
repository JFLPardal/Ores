#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"
#include "DirectionToVector.h"

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow)
{
	m_bricks.resize(Consts::NUM_MAX_COLUMNS);
	m_currentNumColumns = m_bricks.size();
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
				std::set<std::pair<uint, uint>> indexesToDelete;
				FindSequenceStartingIn(m_clickedBrick, indexesToDelete);
				printf("Indexes to delete:\n");
				
				for(auto& indexToDelete : indexesToDelete)
				{
					printf("(%d,%d)\n", indexToDelete.first, indexToDelete.second);
				}
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

//uPtr<std::set<std::pair<size_t, size_t>>> Game::FindSequenceStartingIn(const Brick& brick) const
void Game::FindSequenceStartingIn(const Brick& brick, std::set<std::pair<uint, uint>>& indexesToDelete) const
{
	const uint numDirections = Consts::NUM_DIRECTIONS;
	
	// find clicked brick index
	auto clickedBrickPosition = GridPositionOfBrick(brick);
	indexesToDelete.insert(clickedBrickPosition);
	// for each direction U,R,D,L
	for(auto& index : indexesToDelete)
	{
		for(size_t dirToCheck = 0; dirToCheck < numDirections; dirToCheck++)
		{
			// check if brick in that direction is of the same type
			auto positionToCheck = GetBrickRelativePosition(index, (Direction) dirToCheck);
			if(IsPositionValid(positionToCheck))
			{
				// if they are the same type, add them to indicesToDelete
				if(brick.GetColor() == m_bricks[positionToCheck.first][positionToCheck.second]->GetColor())
				{
					indexesToDelete.insert(positionToCheck);
				}
			}
		}
	}
}

std::pair<int, int> Game::GridPositionOfBrick(const Brick& brick) const
{
	const int gridInitialX = Consts::INITIAL_BRICK_X;
	const int gridInitialY = Consts::INITIAL_BRICK_Y;
	const int brickW = Consts::BRICK_W;
	const int brickH = Consts::BRICK_H;
	
	for(size_t x = 1; x < m_bricks.size(); x++)
	{
		if(brick.GetTransform().X() > gridInitialX - brickW * x)
		{
			for (size_t y = 1; x < m_bricks.size(); y++)
			{
				if (brick.GetTransform().Y() < gridInitialY + brickH * y)
				{
					return std::pair<int,int>{--x,--y};
				}
			}
		}
	}
	return std::pair<int, int>{-1, -1};
}

std::pair<int, int> Game::GetBrickRelativePosition(std::pair<uint, uint> brickPositionInGrid, Direction direction) const
{
	std::pair<int, int> relativePos;
	auto dirToVector = DirectionToVector::GetInstance();	// usar como member variable
	relativePos.first = brickPositionInGrid.first + dirToVector->GetXIncrement(direction);
	relativePos.second = brickPositionInGrid.second + dirToVector->GetYIncrement(direction);

	return relativePos;
}

bool Game::IsPositionValid(std::pair<int, int> position) const
{
	if(position.first >= 0 && position.first < m_currentNumColumns && position.second >= 0 && position.second < Consts::BRICKS_PER_COLUMN)
	{
		return true;
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