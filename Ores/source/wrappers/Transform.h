#pragma once
#include <Aliases.h>
#include "SDL.h"

struct SDL_Rect;

class Transform
{
public:
	Transform();
	Transform(int x, int y, uint w, uint h);
	~Transform();
	Transform(const Transform& transform);

	void SetX(int x) { m_rect.x = x; }
	uint Width() const { return m_rect.w; }
	uint Height() const { return m_rect.h; }
	int X() const { return m_rect.x; }
	int Y() const { return m_rect.y; }
	SDL_Rect Rect() const { return m_rect; }
	
private:
	void SetRect(int x, int y, uint w, uint h);
	SDL_Rect m_rect;
};