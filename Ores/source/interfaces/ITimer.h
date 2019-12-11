#pragma once

class ITimer
{
public:
	virtual void Init(float secondsToCallFunction, SDL_TimerCallback functionToCall) = 0;
	virtual void Update() = 0;
	virtual void Remove() = 0;
};