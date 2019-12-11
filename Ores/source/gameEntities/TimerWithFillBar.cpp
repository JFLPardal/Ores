#include "pch.h"
#include "TimerWithFillBar.h"

void TimerWithFillBar::Init(float secondsToCallFunction, SDL_TimerCallback functionToCall)
{
	int s = 0;
	m_functionToCall = functionToCall;
	m_secondsBetweenCalls = secondsToCallFunction;
	m_timerID = SDL_AddTimer(secondsToCallFunction * 1000, functionToCall, &s);
}

void TimerWithFillBar::Update()
{
	Remove();
	int s = 0;
	m_timerID = SDL_AddTimer(m_secondsBetweenCalls * 1000, m_functionToCall, &s);
}

void TimerWithFillBar::Remove()
{
	SDL_RemoveTimer(m_timerID);
}
