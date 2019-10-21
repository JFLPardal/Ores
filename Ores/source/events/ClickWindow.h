#pragma once
#include "IClickEvent.h"
/*#include "Aliases.h"
#include "ParticleSystemManager.h"*/

class ClickWindow : public IClickEvent
{
public:
	ClickWindow();
	~ClickWindow() = default;
	void PlayerClickedWindow(SDL_Event& event, IGrid& grid) override;
private:
	//uPtr<ParticleSystemManager> m_particleManager;
};
