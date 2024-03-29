#pragma once
#include "GameObject.h"
#include "Enums.h"

class IGrid;

class Brick : public GameObject
{
public:
	Brick();
	Brick(int x, int y);
	~Brick() = default;

	void Draw() const override;
	void Update() override;

	bool IntersectWithPoint(int x, int y) { return m_transform.IntersectWithPoint(x, y); }
	BrickColor GetColor() const { return m_color; }
	void UpdatePosition(int x, int y);
private:
	BrickColor m_color;
	std::pair<uint, uint> m_gridPosition;
};