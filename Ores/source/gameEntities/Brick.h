#pragma once
#include "GameObject.h"
#include "Enums.h"

class Brick : public GameObject
{
public:
	Brick();
	Brick(int x, int y);
	Brick(const Brick& brick); // TODO delete this, for debug only
	~Brick();

	void Draw() const override;
	
	BrickColor GetColor() const { return m_color; }
private:
	BrickColor m_color;
};