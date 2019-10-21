#include "GameObject.h"

#include "Transform.h"
#include "Constants.h"
#include "TextureManager.h"

uint GameObject::m_nextId = 0;

GameObject::GameObject()
	: m_id(m_nextId), m_transform(0, 0, Consts::DEFAULT_W, Consts::DEFAULT_H)
{
	NextID();
}

GameObject::GameObject(int x, int y)
	: m_id(m_nextId), m_transform(x, y, Consts::DEFAULT_W, Consts::DEFAULT_H)
{
	NextID();
}

GameObject::GameObject(int x, int y, int w, int h)
	: m_id(m_nextId), m_transform(x, y, w, h)
{
	NextID();
}

void GameObject::Draw() const
{
	TextureManager::Draw(this);
}

void GameObject::Update()
{
}

void GameObject::NextID()
{
	m_nextId++;
}
