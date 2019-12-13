#pragma once

#include "Constants.h"
#include "SDL_rect.h"
#include "Transform.h"

struct Bar
{
	Bar(int x, int y, bool isBackgroungBar)
		:m_position(Transform(x, y, Consts::UI_BAR_W, Consts::UI_BAR_H)),
		m_bIsBackground(isBackgroungBar)
	{}

	Transform GetTransform() const { return m_position; }
	bool IsBackgroundBar() const { return m_bIsBackground; }

	void SetMaxCapacity(int newMaxCapacity) { m_position.UpdateW(newMaxCapacity); }
private:
	Transform m_position;
	bool m_bIsBackground;
};
