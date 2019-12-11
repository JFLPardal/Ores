#pragma once

#include "Constants.h"
#include "Bar.h"
#include "TextureManager.h"
#include "Transform.h"

class IUIBar
{
public:
	virtual void Fill() = 0;
protected:
	Bar* m_background;
	Bar* m_foreground;
};

