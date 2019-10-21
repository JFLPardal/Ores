#include "pch.h"
#include "ClickWindow.h"
#include "IGrid.h"
#include "ParticleSystemManager.h"

ClickWindow::ClickWindow()
	//:m_particleManager(std::make_unique<ParticleSystemManager>())
{
	
}


void ClickWindow::PlayerClickedWindow(SDL_Event& event, IGrid& grid)
{
	if (grid.IsBrickOnClickedPosition(event.button.x, event.button.y))
	{
		ParticleSystemManager::FireParticles(clickOnBrick, event.button.x, event.button.y);
		//m_particleManager->FireParticles(clickOnBrick, event.button.x, event.button.y);
		std::set<std::pair<uint, uint>> indexesToDelete;
		grid.FindSequenceInClick(indexesToDelete);
		if (indexesToDelete.size() > 1)
		{
			grid.DeleteSequence(indexesToDelete);
			grid.DeleteEmptyColumns();
			grid.UpdatePositionOfBricks();
		}
	}
	else
	{
		ParticleSystemManager::FireParticles(clickOnVoid, event.button.x, event.button.y);
		//m_particleManager->FireParticles(clickOnVoid, event.button.x, event.button.y);
	}
}
