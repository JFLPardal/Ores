#pragma once

#include "Aliases.h"
#include "ITimer.h"
#include "IUIBar.h"

class TimerWithFillBar : public ITimer
{
public:
	TimerWithFillBar();
	~TimerWithFillBar() = default;

	void Init(float secondsBetweenCalls, SDL_TimerCallback functionToCall) override;
	void ChangeSecondsBetweenCalls(float newSecondsBetweenCalls) override;
	void Clear() override;
	IUIBar* GetUIBar() const;// return reference to vvv IUIBar so that Game.cpp can call Draw on it
private:
	std::shared_ptr<IUIBar> m_TimerAsPercentageBar;
};

