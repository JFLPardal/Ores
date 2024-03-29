#pragma once
#include "IGrid.h"
#include "Enums.h"
#include "Brick.h"

class MatrixGrid : public IGrid
{
public:
	MatrixGrid();
	~MatrixGrid() = default;

	void Init() override;
	void InitBricks() override;
	void Draw() override;
	void Update() override;

	uint CurrentNumberOfColumns() const override { return m_currentNumColumns; }
	bool IsBrickOnClickedPosition(int x, int y) override;
	void FindSequenceInClick(std::set<std::pair<uint, uint>>& IndexesToDelete) const override;

	void DeleteSequence(const std::set<std::pair<uint, uint>>& indexesToDelete) override;
	void DeleteEmptyColumns() override;
	void UpdatePositionOfBricks() override;
	void SpawnColumn() override;
	void ClearGrid() override;
private:
	void InitBrickColumn(uint column);
	std::pair<int, int> GridPositionOfBrick(const Brick& brick) const;
	std::pair<int, int> GetBrickRelativePosition(std::pair<uint, uint> brickPositionInGrid, Direction direction) const;
	bool IsPositionValid(std::pair<uint, uint> position) const;

	void PrintIndexesToDelete(std::set<std::pair<uint, uint>>& indexesToDelete) const;
private:
	std::vector<std::vector<Brick>> m_bricks;
	Brick m_clickedBrick;
	uint m_currentNumColumns;
};
