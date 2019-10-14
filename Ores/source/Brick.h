#pragma once
#include "GameObject.h"

enum BrickColor;

class Brick : public GameObject
{
public:
	Brick();
	~Brick();
	
	BrickColor GetColor() const { return m_color; }
private:
	BrickColor m_color;
};