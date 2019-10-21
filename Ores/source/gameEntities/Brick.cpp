#include "Brick.h"
#include "Enums.h"
#include "TextureManager.h"
#include "Constants.h"

Brick::Brick()
	:m_color(BrickColor(rand()%Consts::NUM_DIF_BRICKS))
{
}

Brick::Brick(int x, int y)
	:GameObject(Consts::INITIAL_BRICK_X - x * Consts::BRICK_W, 
				Consts::INITIAL_BRICK_Y - y * Consts::BRICK_H, 
				  Consts::BRICK_W, 
				  Consts::BRICK_H),
		m_color(BrickColor(rand() % Consts::NUM_DIF_BRICKS)),
		m_gridPosition(x,y)
{
}

void Brick::Draw() const
{
	TextureManager::Draw(this);
}

void Brick::Update()
{
	m_transform.UpdatePosition(Consts::INITIAL_BRICK_X - m_gridPosition.first * Consts::BRICK_W,
							   Consts::INITIAL_BRICK_Y - m_gridPosition.second * Consts::BRICK_H); // not caching this values for memory reasons
}

void Brick::UpdatePosition(int x, int y)
{
	m_gridPosition.first = x;
	m_gridPosition.second = y;
}
