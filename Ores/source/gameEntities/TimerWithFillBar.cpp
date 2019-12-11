#include "pch.h"
#include "TimerWithFillBar.h"

void TimerWithFillBar::Init(float secondsBetweenCalls, SDL_TimerCallback functionToCall)
{
	int s = 0;
	m_functionToCall = functionToCall;
	m_secondsBetweenCalls = secondsBetweenCalls;
	m_timerID = SDL_AddTimer(secondsBetweenCalls * 1000, functionToCall, &s);
}

void TimerWithFillBar::ChangeSecondsBetweenCalls(float newSecondsBetweenCalls)
{
	Remove();
	int s = 0;
	m_secondsBetweenCalls = newSecondsBetweenCalls;
	m_timerID = SDL_AddTimer(newSecondsBetweenCalls * 1000, m_functionToCall, &s);
}

void TimerWithFillBar::Remove()
{
	SDL_RemoveTimer(m_timerID);
}
