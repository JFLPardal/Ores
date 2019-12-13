#include "pch.h"
#include "FillBar.h"

FillBar::FillBar(int screenCoordX, int screenCoordY)
{
	m_lastGameTick = SDL_GetTicks();
	m_background = new Bar(screenCoordX, screenCoordY, true);
	m_foreground = new Bar(screenCoordX, screenCoordY, false);
}

void FillBar::MaxCapacity(float maxCapacityInUnits)
{
	m_timeRemaining = maxCapacityInUnits;
	m_timeToDepleteBar = maxCapacityInUnits;
	m_maxCapacityWidth = Consts::UI_BAR_W;
	m_foreground->SetMaxCapacity(Consts::UI_BAR_W);
}

void FillBar::Update()
{
	m_timeRemaining = m_timeRemaining - (SDL_GetTicks() - m_lastGameTick) * MS_TO_S;
	float currentCapacityAsPercentage = GetCapacityAsPercentagePoint();
	m_foreground->SetMaxCapacity((int)(m_maxCapacityWidth * currentCapacityAsPercentage));
	m_lastGameTick = SDL_GetTicks();
}

void FillBar::Draw()
{
	TextureManager::Draw(m_background);
	TextureManager::Draw(m_foreground);
}

float FillBar::GetCapacityAsPercentagePoint() const
{
	float fillAsPercentage = ((float)m_timeRemaining * 100 / m_timeToDepleteBar) * .01f;
	return fillAsPercentage;
}

FillBar::~FillBar()
{
	delete m_background;
	delete m_foreground;
}

