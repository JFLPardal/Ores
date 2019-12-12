#pragma once

#include "Constants.h"

class ITimer
{
public:
	virtual void Init(float secondsBetweenCalls, SDL_TimerCallback functionToCall) = 0;
	virtual void ChangeSecondsBetweenCalls(float newSecondsBetweenCalls) = 0;
	virtual void Clear() = 0;
protected:
	SDL_TimerCallback m_functionToCall;
	float m_timerID;
	float m_secondsBetweenCalls;
};