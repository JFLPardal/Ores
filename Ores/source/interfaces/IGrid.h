#pragma once
#include "Aliases.h"

#include <set> // TODO delete after encapsulating set

class Brick;

class IGrid
{
public:
	virtual ~IGrid() = default;
	virtual void Init() = 0;
	virtual void InitBricks() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;

	virtual uint CurrentNumberOfColumns() const = 0;
	virtual bool IsBrickOnClickedPosition(int x, int y, Brick& brickToStoreData) = 0;
	virtual void FindSequenceStartingIn(const Brick& clickedBrick, std::set<std::pair<uint, uint>>& IndexesToDelete) const = 0;
		
	virtual void DeleteSequence(const std::set<std::pair<uint, uint>>& indexesToDelete) = 0;
	virtual void DeleteEmptyColumns() = 0;
	virtual void UpdatePositionOfBricks() = 0;
	virtual void SpawnColumn() = 0;
	virtual void ClearGrid() = 0;
};