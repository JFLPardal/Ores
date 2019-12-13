#pragma once
#include "IUIBar.h"

class FillBar : public IUIBar
{
public:
	FillBar(int screenCoordX, int screenCoordY);
	~FillBar();

	void MaxCapacity(float maxCapacityInUnits) override;
	void Update() override;
	void Draw() override;
	bool IsBackgroundBar() {}
private:
	// The value returned is a float between 0 and 1
	float GetCapacityAsPercentagePoint() const;
private:
	uint m_maxCapacityWidth;
	Uint32 m_lastGameTick = 0;
	float m_timeRemaining = -1;
	float m_timeToDepleteBar;
	const float MS_TO_S = 1.f / 1000;
};