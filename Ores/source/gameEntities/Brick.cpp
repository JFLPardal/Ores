#include "Brick.h"
#include "Enums.h"
#include "TextureManager.h"
#include "Constants.h"

Brick::Brick()
	:m_color(BrickColor(rand()%Consts::NUM_DIF_BRICKS))
{
	printf("default brick created\n");
}

Brick::Brick(int x, int y)
	:GameObject(Consts::INITIAL_BRICK_X - x * Consts::BRICK_W, 
		Consts::INITIAL_BRICK_Y - y * Consts::BRICK_H),
		m_color(BrickColor(rand() % 3)),
		m_gridPosition(x,y)
{
	printf("brick created\n");
}

Brick::Brick(const Brick& brick)
{
	printf("copied brick");
}

void Brick::Update()
{
	m_transform.UpdatePosition(m_gridPosition.first, m_gridPosition.second);
}

void Brick::Draw() const
{
	TextureManager::Draw(this);
}

Brick::~Brick()
{
	printf("brick destroyed\n");
}
