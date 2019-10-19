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

	uint Width() const { return m_rect.w; }
	uint Height() const { return m_rect.h; }
	int X() const { return m_rect.x; }
	int Y() const { return m_rect.y; }
	SDL_Rect Rect() const { return m_rect; }
	void UpdatePosition(int x, int y);
	
private:
	void SetX(int x) { m_rect.x = x; }
	void SetY(int y) { m_rect.y = y; }
private:
	void SetRect(int x, int y, uint w, uint h);
	SDL_Rect m_rect;
};