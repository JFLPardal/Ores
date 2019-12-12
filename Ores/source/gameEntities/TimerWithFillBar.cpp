#include "pch.h"
#include "TimerWithFillBar.h"
#include "FillBar.h"

TimerWithFillBar::TimerWithFillBar()
	:m_TimerAsPercentageBar(std::make_shared<FillBar>(Consts::UI_BAR_X, Consts::UI_BAR_Y))
{
}

void TimerWithFillBar::Init(float secondsBetweenCalls, SDL_TimerCallback functionToCall)
{
	int s = 0;
	UpdateBarsMaxCapacity(secondsBetweenCalls);
	m_functionToCall = functionToCall;
	m_secondsBetweenCalls = secondsBetweenCalls;
	m_timerID = SDL_AddTimer(secondsBetweenCalls * 1000, functionToCall, &s);
}

void TimerWithFillBar::ChangeSecondsBetweenCalls(float newSecondsBetweenCalls)
{
	Clear();
	int s = 0;
	UpdateBarsMaxCapacity(newSecondsBetweenCalls);
	m_secondsBetweenCalls = newSecondsBetweenCalls;
	m_timerID = SDL_AddTimer(newSecondsBetweenCalls * 1000, m_functionToCall, &s);
}

void TimerWithFillBar::Clear()
{
	SDL_RemoveTimer(m_timerID);
}

IUIBar* TimerWithFillBar::GetUIBar() const
{
	return m_TimerAsPercentageBar.get();
}

void TimerWithFillBar::UpdateBarsMaxCapacity(float newMaxCapacity) const
{
	m_TimerAsPercentageBar->MaxCapacity(newMaxCapacity);
}
