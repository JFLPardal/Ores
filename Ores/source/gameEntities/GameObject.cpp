#include "GameObject.h"

#include "Transform.h"
#include "Constants.h"
#include "TextureManager.h"

uint GameObject::m_nextId = 0;

GameObject::GameObject()
	: m_id(m_nextId), m_transform(0, 0, Consts::BRICK_W, Consts::BRICK_H)
{
	NextID();
	printf("GO created\n");
}

GameObject::GameObject(int x, int y)
	: m_id(m_nextId), m_transform(x, y, Consts::BRICK_W, Consts::BRICK_H)//, m_sprite(std::make_unique<SDLSprite>())
{
	NextID();
	printf("GO created\n");
}

GameObject::GameObject(int x, int y, int w, int h)
	: m_id(m_nextId), m_transform(x, y, w, h)//, m_sprite(std::make_unique<SDLSprite>())
{
	NextID();
	printf("GO created\n");
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
