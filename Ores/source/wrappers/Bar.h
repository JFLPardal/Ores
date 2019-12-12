#pragma once

#include "Constants.h"
#include "SDL_rect.h"
#include "Transform.h"

struct Bar
{
	Transform m_position;
	
	Bar(int x, int y)
		:m_position(Transform(x, y, Consts::UI_BAR_W, Consts::UI_BAR_H))
	{}

	Transform GetTransform() const { return m_position; }
};
