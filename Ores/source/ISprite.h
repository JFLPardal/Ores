#pragma once
#include <cstdio>	// TODO remove

class ISprite
{
public:
	virtual ~ISprite() { printf("ISprite deleted\n"); }
	virtual void Draw() const = 0;
	virtual void LoadSprite(const char* spritePath) = 0;
};