#pragma once
#include <cstdio>	// TODO remove
#include <string>

class ISprite
{
public:
	virtual ~ISprite() { printf("ISprite deleted\n"); }
	virtual void Draw() const = 0;
	virtual void SetSprite(std::string spritePath) = 0;
};