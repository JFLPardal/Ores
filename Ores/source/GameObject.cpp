#include "GameObject.h"
#include <cstdio>	//remove
#include "SDLSprite.h"

uint GameObject::m_nextId = 0;

GameObject::GameObject()
	: m_id(m_nextId), m_sprite(std::make_unique<SDLSprite>())
{
	m_nextId++;
	printf("GO created\n");
}

void GameObject::Draw() const
{
	// ISprite.Draw();
}

void GameObject::Update()
{
	
}

GameObject::~GameObject()
{
	printf("GO destroyed\n");
}
