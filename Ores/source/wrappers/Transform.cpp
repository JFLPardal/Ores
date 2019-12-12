#include "pch.h"

#include "Transform.h"
#include "Constants.h"

Transform::Transform()
	:m_rect()
{
	SetRect(0, 0, Consts::DEFAULT_W, Consts::DEFAULT_H);
}

Transform::Transform(int x, int y, uint w, uint h)
	:m_rect()
{
	SetRect(x, y, w, h);
}

Transform::Transform(const Transform& transform)
{
	SetRect(transform.Rect().x, transform.Rect().y, transform.Rect().w, transform.Rect().h);
}

void Transform::UpdatePosition(int x, int y)
{
	SetX(x);
	SetY(y);
}

void Transform::UpdateW(int newW)
{
	m_rect.w = newW;
}

void Transform::SetRect(int x, int y, uint w, uint h)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = w;
	m_rect.h = h;
}

bool Transform::IntersectWithPoint(int x, int y)
{
	SDL_Point positionClicked{ x, y };
	return SDL_PointInRect(&positionClicked, &m_rect); 
}

