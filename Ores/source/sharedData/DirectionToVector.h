#pragma once
#include <memory>
#include <map>
#include "Enums.h"

class DirectionToVector
{
public:
	static std::unique_ptr<DirectionToVector> m_instance;
	static DirectionToVector* GetInstance();
	int GetXIncrement(Direction direction);
	int GetYIncrement(Direction direction);
private:
	std::map<Direction, std::pair<int, int>> m_directionToVector;
	DirectionToVector();
};