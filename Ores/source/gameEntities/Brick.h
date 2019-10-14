#pragma once
#include "GameObject.h"
#include "Enums.h"

class Brick : public GameObject
{
public:
	Brick();
	Brick(int x, int y);
	~Brick();

	void Draw() const override;
	
	BrickColor GetColor() const { return m_color; }
private:
	BrickColor m_color;
};