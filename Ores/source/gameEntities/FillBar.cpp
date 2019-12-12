#include "pch.h"
#include "FillBar.h"

FillBar::FillBar(int screenCoordX, int screenCoordY)
{
	m_lastGameTick = SDL_GetTicks();
	m_background = new Bar(screenCoordX, screenCoordY);
	m_foreground = new Bar(screenCoordX, screenCoordY);
	auto bar = m_background->GetTransform();
	printf("bar created on x: %d, y:%d with w: %d and h: %d", bar.X(), bar.Y(), bar.Width(), bar.Height());
}

void FillBar::MaxCapacity(float maxCapacity)
{
	m_maxCapacity = Consts::UI_BAR_W;
	m_currentCapacity = m_maxCapacity;
	m_foreground->SetMaxCapacity((int)maxCapacity);
}

void FillBar::Update()
{
	m_currentCapacity = m_currentCapacity - (SDL_GetTicks() - m_lastGameTick)  * FRAME_DURATION;
	int currentCapacityHasPercentage = GetCapacityAsPercentage();
	m_foreground->SetMaxCapacity(currentCapacityHasPercentage);
	m_lastGameTick = SDL_GetTicks();
}

void FillBar::Draw()
{
	TextureManager::Draw(m_background);
	TextureManager::Draw(m_foreground);
}

void FillBar::Fill()
{

}

int FillBar::GetCapacityAsPercentage() const
{
	int fillAsPercentage = std::floor(m_currentCapacity * 100 / m_maxCapacity);
	fillAsPercentage = std::clamp(fillAsPercentage, 0, 100);
	printf("%d\n", fillAsPercentage);
	return fillAsPercentage;
}

FillBar::~FillBar()
{
	delete m_background;
	delete m_foreground;
}

