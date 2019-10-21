#include "pch.h"
#include "Particle.h"
#include "RNGFunctions.h"
#include "Constants.h"
#include "TextureManager.h"

Particle::Particle()
	:GameObject(0,0),
	m_isAlive(true),
	m_lifetime(RNG::RandomInt((int)Consts::MIN_PARTICLE_LIFETIME, (int)Consts::MAX_PARTICLE_LIFETIME)),
	m_velocity({ RNG::RandomInt(-1, 1),RNG::RandomInt(1, 2) })
{
}

Particle::Particle(int x, int y)
	:GameObject(x,y),
	m_isAlive(true),
	m_lifetime(RNG::RandomInt((int)Consts::MIN_PARTICLE_LIFETIME, (int) Consts::MAX_PARTICLE_LIFETIME)),
	m_velocity({ RNG::RandomInt(-1, 1),RNG::RandomInt(1, 2) })
{
}

void Particle::Update()
{
	if(IsAlive())
	{
		UpdatePosition();
		m_currentLifetime++;
		ValidateLifetime();
	}
}

void Particle::Draw()
{
	if(IsAlive())
	{
		TextureManager::Draw(this);
	}
}

void Particle::ChangePosition(int x, int y)
{
	m_transform.UpdatePosition(x, y);
}

void Particle::UpdatePosition()
{
	m_transform.UpdatePosition(m_transform.X() + m_velocity.first, m_transform.Y() + m_velocity.second);
}

void Particle::ResetState()
{
	m_currentLifetime = 0;
	m_isAlive = true;
}
