#pragma once

#include "Constants.h"
#include "Bar.h"
#include "TextureManager.h"
#include "Transform.h"

class IUIBar
{
public:
	virtual void MaxCapacity(float maxCapacity) = 0;
	virtual void Fill() = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
protected:
	Bar* m_background;
	Bar* m_foreground;
};

