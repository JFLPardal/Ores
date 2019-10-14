#include "Brick.h"
#include "SDLSprite.h"
#include "Enums.h"
#include "Constants.h"

Brick::Brick()
	:m_color(Blue)
{
	printf("brick created\n");
	m_sprite->SetSprite(Consts::imagePath);
}

Brick::~Brick()
{
	printf("brick destroyed\n");
}
