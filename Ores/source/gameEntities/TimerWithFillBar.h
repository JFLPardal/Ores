#pragma once

#include "ITimer.h"

class TimerWithFillBar : public ITimer
{
public:
	TimerWithFillBar() = default;
	~TimerWithFillBar() = default;

	void Init(float secondsToCallFunction, SDL_TimerCallback functionToCall) override;
	void Update() override;
	void Remove() override;
private:
	SDL_TimerID m_timerID;
	SDL_TimerCallback m_functionToCall;
	float m_secondsBetweenCalls;
};

