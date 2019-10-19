#include "pch.h"

#include "Transform.h"
#include "Constants.h"

Transform::Transform()
	:m_rect()
{
	SetRect(0, 0, Consts::BRICK_W, Consts::BRICK_H);
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
	SetX(Consts::INITIAL_BRICK_X - x * Consts::BRICK_W);
	SetY(Consts::INITIAL_BRICK_Y + y * Consts::BRICK_H);
}

void Transform::SetRect(int x, int y, uint w, uint h)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = w;
	m_rect.h = h;
}

Transform::~Transform()
{	
}

