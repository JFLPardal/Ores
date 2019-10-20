#include "pch.h"
#include "MatrixGrid.h"
#include "Constants.h"
#include "Brick.h"
#include "Enums.h"
#include "DirectionToVector.h"

MatrixGrid::MatrixGrid()
	:m_currentNumColumns(0)
{
}

void MatrixGrid::Init()
{
	m_currentNumColumns = Consts::NUM_INITIAL_COLUMNS;
	m_bricks.reserve(Consts::NUM_MAX_COLUMNS);
	m_bricks.resize(m_currentNumColumns);
	for (size_t column = 0; column < m_currentNumColumns; column++)
	{
		m_bricks[column].reserve(Consts::BRICKS_PER_COLUMN);
	}
}

void MatrixGrid::InitBricks() 
{
	for (size_t column = 0; column < m_currentNumColumns; column++)
	{
		InitBrickColumn(column);
	}
}

void MatrixGrid::InitBrickColumn(uint column) 
{
	for (size_t row = 0; row < Consts::BRICKS_PER_COLUMN; row++)
	{
		m_bricks[column].emplace_back(column, row); // construct brick on the vertex with these params (saves copies)
	}
}

void MatrixGrid::Update()
{
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			brick.Update();
		}
	}
}

void MatrixGrid::Draw()
{
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{
			brick.Draw();
		}
	}
}

void MatrixGrid::ClearGrid()
{
	m_bricks.clear();
}

bool MatrixGrid::IsBrickOnClickedPosition(int x, int y) // TODO make this more efficient
{
	for (auto& column : m_bricks)
	{
		for (auto& brick : column)
		{			
			if (brick.IntersectWithPoint(x, y))
			{
				m_clickedBrick = brick;
				return true;
			}
		}
	}
	return false;
}

std::pair<int, int> MatrixGrid::GridPositionOfBrick(const Brick& brick) const
{
	const uint gridInitialX = Consts::INITIAL_BRICK_X;
	const uint gridInitialY = Consts::INITIAL_BRICK_Y;
	const uint brickW = Consts::BRICK_W;
	const uint brickH = Consts::BRICK_H;
	const uint bricksPerColumn = Consts::BRICKS_PER_COLUMN;
	const uint BrickX = brick.GetTransform().X();
	const uint BrickY = brick.GetTransform().Y();
	
	for (size_t x = 1; x <= m_bricks.size(); x++)
	{
		if (BrickX > gridInitialX - brickW * x)
		{
			for (size_t y = 1; y < bricksPerColumn; y++)
			{
				if (BrickY > gridInitialY - brickH * y)
				{
					return std::pair<int, int>{--x, --y};
				}
			}
		}
	}
	return std::pair<int, int>{-1, -1};
}
// This functions uses 2 data structures: 1) a set to keep all the (unique) pairs of indexes that are to be deleted
// and 2) a queue that holds all the pairs of indexes that still need to be color tested against the clicked brick 
void MatrixGrid::FindSequenceInClick(std::set<std::pair<uint, uint>>& indexesToDelete) const
{
	const auto clickedBrickPosition = GridPositionOfBrick(m_clickedBrick);
	indexesToDelete.insert(clickedBrickPosition);
	std::queue<std::pair<uint, uint>> queue;
	queue.push(clickedBrickPosition);
	
	const uint numDirections = Consts::NUM_DIRECTIONS;
	const auto clickedBrickColor = m_clickedBrick.GetColor();
	
	while (!queue.empty())
	{
		const auto currentPosition = queue.front();
		for (size_t dirToCheck = 0; dirToCheck < numDirections; dirToCheck++)
		{
			auto positionToCheck = GetBrickRelativePosition(currentPosition, (Direction) dirToCheck);
			if (IsPositionValid(positionToCheck))
			{
				if (clickedBrickColor == m_bricks[positionToCheck.first][positionToCheck.second].GetColor())
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
// this screen position update is done in void MatrixGrid::UpdatePositionOfBricks()
void MatrixGrid::DeleteSequence(const std::set<std::pair<uint, uint>>& indexesToDelete)
{
	std::set<std::pair<uint, uint>>::reverse_iterator rit;
	for (rit = indexesToDelete.rbegin(); rit != indexesToDelete.rend(); ++rit)
	{
		const auto posToDelete = m_bricks[rit->first].begin() + rit->second;
		m_bricks[rit->first].erase(posToDelete);
	}
}

std::pair<int, int> MatrixGrid::GetBrickRelativePosition(std::pair<uint, uint> brickPositionInGrid, Direction direction) const
{
	std::pair<int, int> relativePos;
	auto dirToVector = DirectionToVector::GetInstance();
	relativePos.first = brickPositionInGrid.first + dirToVector->GetXIncrement(direction);
	relativePos.second = brickPositionInGrid.second + dirToVector->GetYIncrement(direction);

	return relativePos;
}

bool MatrixGrid::IsPositionValid(std::pair<uint, uint> position) const
{
	if (position.first >= 0 && position.first < m_currentNumColumns && position.second >= 0 && position.second < Consts::BRICKS_PER_COLUMN)
	{
		if (m_bricks[position.first].size() > position.second)
		{
			return true;
		}
	}
	return false;
}

void MatrixGrid::SpawnColumn()
{
	m_bricks.emplace(m_bricks.begin(), std::vector<Brick>{});
	m_bricks[0].reserve(Consts::BRICKS_PER_COLUMN);
	m_currentNumColumns++;
	InitBrickColumn(0);
}

void MatrixGrid::DeleteEmptyColumns()
{
	for (size_t x = 0; x < m_currentNumColumns; x++)
	{
		if (m_bricks[x].empty())
		{
			const auto columnToDelete = m_bricks.begin() + x;
			m_bricks.erase(columnToDelete);
			m_currentNumColumns--;
			x--;
		}
	}
}

void MatrixGrid::UpdatePositionOfBricks()
{
	for (size_t x = 0; x < m_bricks.size(); x++)
	{
		for (size_t y = 0; y < m_bricks[x].size(); y++)
		{
			m_bricks[x][y].UpdatePosition(x, y);
		}
	}
}

MatrixGrid::~MatrixGrid()
{
	printf("matrixGrid deleted");
}
