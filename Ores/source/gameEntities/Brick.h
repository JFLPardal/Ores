#pragma once
#include "GameObject.h"
#include "Enums.h"

class IGrid;

class Brick : public GameObject
{
public:
	Brick();
	Brick(int x, int y);
	Brick(const Brick& brick); // TODO delete this, for debug only
	~Brick();

	void Draw() const override;
	void Update() override;
	
	BrickColor GetColor() const { return m_color; }
	void UpdatePosition(int x, int y);
private:
	BrickColor m_color;
	std::pair<uint, uint> m_gridPosition;
};