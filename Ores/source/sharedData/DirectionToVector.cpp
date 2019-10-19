#include "pch.h"

#include "DirectionToVector.h"

std::unique_ptr<DirectionToVector> DirectionToVector::m_instance{ nullptr };// std::make_unique<DirectionToVector>();
//std::map<Direction, std::pair<int, int>> DirectionToVector::m_directionToVector;

DirectionToVector::DirectionToVector()
{
	m_directionToVector.emplace(Direction::Up,    std::pair<int,int>(0, 1));	
	m_directionToVector.emplace(Direction::Right, std::pair<int,int>(-1, 0));	// X increases from right to left
	m_directionToVector.emplace(Direction::Down,  std::pair<int,int>(0, -1));
	m_directionToVector.emplace(Direction::Left,  std::pair<int,int>(1, 0));
}

int DirectionToVector::GetXIncrement(Direction direction) 
{
	return m_directionToVector[direction].first;
}

int DirectionToVector::GetYIncrement(Direction direction) 
{
	return m_directionToVector[direction].second;
}

DirectionToVector* DirectionToVector::GetInstance()
{
	if (!m_instance)
		m_instance = std::make_unique<DirectionToVector>(DirectionToVector());
	return m_instance.get();
}