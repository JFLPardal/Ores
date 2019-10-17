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
	:GameObject(x,y), m_color(BrickColor(rand() % Consts::NUM_DIF_BRICKS))
{
	printf("brick created\n");
}

Brick::Brick(const Brick& brick)
{
	printf("copied brick");
}

void Brick::Draw() const
{
	TextureManager::Draw(this);
}

Brick::~Brick()
{
	printf("brick destroyed\n");
}
