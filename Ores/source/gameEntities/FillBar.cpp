#include "pch.h"
#include "FillBar.h"

FillBar::FillBar(int screenCoordX, int screenCoordY)
{
	m_background = new Bar(screenCoordX, screenCoordY);
	//m_background.Init(screenCoordX, screenCoordY);
	auto bar = m_background->GetTransform();
	printf("bar created on x: %d, y:%d with w: %d and h: %d", bar.X(), bar.Y(), bar.Width(), bar.Height());
}



void FillBar::Fill()
{

}

FillBar::~FillBar()
{
	delete m_background;
	delete m_foreground;
}

