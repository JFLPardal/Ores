#pragma once

#include "ITimer.h"

class TimerWithFillBar : public ITimer
{
public:
	TimerWithFillBar() = default;
	~TimerWithFillBar() = default;

	void Init(float secondsBetweenCalls, SDL_TimerCallback functionToCall) override;
	void ChangeSecondsBetweenCalls(float newSecondsBetweenCalls) override;
	void Remove() override;
};

