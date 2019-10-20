#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"
#include "DirectionToVector.h"

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
	:m_window(nullptr, SDL_DestroyWindow)
{
	CreateWindow();
	TextureManager::InitTextureManager(m_window.get());
	InitGame();
}

void Game::InitGame()
{
	m_currentNumColumns = Consts::NUM_INITIAL_COLUMNS;
	InitGrid();
	InitGameObjects();
	InitTimer();
}

void Game::InitGrid()
{
	m_bricks.resize(Consts::NUM_MAX_COLUMNS);
	for (auto& column : m_bricks)
	{
		column.reserve(Consts::BRICKS_PER_COLUMN);
	}
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
	InitBricks();
}

void Game::InitBricks()
{	
	for(size_t column = 0; column < Consts::NUM_INITIAL_COLUMNS; column++)
	{
		InitBrickColumn(column);
	}
}

void Game::InitBrickColumn(uint column)
{
	for (size_t row = 0; row < Consts::BRICKS_PER_COLUMN; row++)
	{
		m_bricks[column].emplace_back(column, row); // construct brick on the vertex with these params (saves copies)
	}
}


void Game::InitTimer()
{
	int s;
	m_spawnNewColumnTimer = SDL_AddTimer(Consts::MS_BETWEEN_COLUMN_SPAWNS, PushSpawnColumnEvent, &s);
}

void Game::Draw()	// TODO refactor for
{
	TextureManager::ClearRender();
	m_warningArea.Draw();
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			brick.Draw();
		}
	}
	TextureManager::PresentRender();
	
}

void Game::Update() // TODO refactor for
{
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			brick.Update();
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
				if(indexesToDelete.size() > 1)
				{
					DeleteSequence(indexesToDelete);
					DeleteEmptyColumns();
					UpdatePositionInGrid();
				}
			}
		}
		if(event->type == SDL_USEREVENT && event->user.code == UserEvent::SpawnColumn)
		{
			if(m_currentNumColumns < Consts::NUM_MAX_COLUMNS)
			{
				SpawnColumn();
			}
			else
			{
				SDL_RemoveTimer(m_spawnNewColumnTimer);
				m_bricks.clear();
				InitGame();
			}
			UpdatePositionInGrid();
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
			if (SDL_PointInRect(&positionClicked, &brick.GetTransform().Rect()))
			{
				m_clickedBrick = brick;
				return true;
			}
		}
	}
	return false;
}

void Game::FindSequenceStartingIn(const Brick& brick, std::set<std::pair<uint, uint>>& indexesToDelete) const
{
	const uint numDirections = Consts::NUM_DIRECTIONS;
	std::queue<std::pair<uint, uint>> queue;
	// find clicked brick index
	auto clickedBrickPosition = GridPositionOfBrick(brick);
	indexesToDelete.insert(clickedBrickPosition);
	queue.push(clickedBrickPosition);

	while(!queue.empty())
	{
		auto currentPosition = queue.front();
		// for each direction U,R,D,L
		for(size_t dirToCheck = 0; dirToCheck < numDirections; dirToCheck++)
		{
			// check if brick in that direction is of the same type
			auto positionToCheck = GetBrickRelativePosition(currentPosition, (Direction) dirToCheck);
			if(IsPositionValid(positionToCheck))
			{
				// if they are the same type, add them to indicesToDelete
				if(brick.GetColor() == m_bricks[positionToCheck.first][positionToCheck.second].GetColor())
				{
					if (indexesToDelete.find(positionToCheck) == indexesToDelete.end())
					{
						indexesToDelete.insert(positionToCheck);
						queue.push(positionToCheck);
					}
				}
			}
		}
		queue.pop();
	}
	printf("Indexes to delete:\n");
	for (auto& indexToDelete : indexesToDelete)
	{
		printf("(%d,%d)\n", indexToDelete.first, indexToDelete.second);
	}
}

// Due to the way std::vector works this function will automatically update the indexes
// of each column when a brick is destroyed but it won't update the screen position of the bricks,
// this screen position update is done in void Game::UpdatePositionInGrid()
void Game::DeleteSequence(const std::set<std::pair<uint, uint>>& indexesToDelete)
{
	std::set<std::pair<uint, uint>>::reverse_iterator rit;
	for(rit = indexesToDelete.rbegin(); rit != indexesToDelete.rend(); ++rit)
	{
		auto posToDelete = m_bricks[rit->first].begin() + rit->second;
		m_bricks[rit->first].erase(posToDelete);
	}
}

void Game::UpdatePositionInGrid()
{
	for (size_t x = 0; x < m_bricks.size(); x++)
	{
		for (size_t y = 0; y < m_bricks[x].size(); y++)
		{
			m_bricks[x][y].m_gridPosition.first = x;
			m_bricks[x][y].m_gridPosition.second = y;
		}
	}
}

void Game::DeleteEmptyColumns()
{
	for (size_t x = 0; x < m_currentNumColumns; x++)
	{
		if (m_bricks[x].empty())
		{
			auto columnToDelete = m_bricks.begin() + x;
			m_bricks.erase(columnToDelete);
			m_currentNumColumns--;
			x--;
		}
	}
}

std::pair<int, int> Game::GridPositionOfBrick(const Brick& brick) const
{
	const int gridInitialX = Consts::INITIAL_BRICK_X;
	const int gridInitialY = Consts::INITIAL_BRICK_Y;
	const int brickW = Consts::BRICK_W;
	const int brickH = Consts::BRICK_H;
	const int bricksPerColumn = Consts::BRICKS_PER_COLUMN;
	
	for(size_t x = 1; x <= m_bricks.size(); x++)
	{
		if(brick.GetTransform().X() > gridInitialX - brickW * x)
		{
			for (size_t y = 1; x < bricksPerColumn; y++)
			{
				if (brick.GetTransform().Y() > gridInitialY - brickH * y)
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
		if(m_bricks[position.first].size() > position.second)
		{
		return true;
		}
	}
	return false;
}

void Game::SpawnColumn()
{
	m_bricks.emplace(m_bricks.begin(), std::vector<Brick>{});
	m_bricks[0].reserve(Consts::BRICKS_PER_COLUMN);
	m_currentNumColumns++;
	InitBrickColumn(0);
}

Game::~Game()
{
	SDL_Quit();
}