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
	void Remove() override;
private:
	uPtr<IUIBar> m_TimerAsPercentageBar;
};

