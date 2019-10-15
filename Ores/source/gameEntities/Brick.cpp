#include "Brick.h"
#include "Enums.h"
#include "TextureManager.h"

Brick::Brick()
	:m_color(Blue)
{
	printf("brick created\n");
}

Brick::Brick(int x, int y)
	:GameObject(x,y), m_color(Blue)
{
	printf("brick created\n");
}

void Brick::Draw() const
{
	TextureManager::Draw(this);
}


Brick::~Brick()
{
	printf("brick destroyed\n");
}
