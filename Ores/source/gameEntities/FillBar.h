#pragma once
#include "IUIBar.h"

class FillBar : public IUIBar
{
public:
	FillBar(int screenCoordX, int screenCoordY);
	~FillBar();

	void MaxCapacity(float maxCapacity) override;
	void Update() override;
	void Draw() override;
	void Fill() override;
private:
	int GetCapacityAsPercentage() const;
private:
	uint m_maxCapacity;
	float m_currentCapacity;
	Uint32 m_lastGameTick;
	const float FRAME_DURATION = Consts::INTENDED_FRAME_DURATION;
};