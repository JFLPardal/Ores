#include "pch.h"
#include "ParticleGroup.h"
#include "Aliases.h"
#include "RNGFunctions.h"
#include "Constants.h"
#include "Particle.h"

ParticleGroup::ParticleGroup()
{
	uint numberOfParticles = RNG::RandomInt(Consts::MIN_NUMBER_PARTICLES, Consts::MAX_NUMBER_PARTICLES);
	m_particles.resize(numberOfParticles);
	
	for (auto& particle : m_particles)
	{
		particle = Particle();
		if(particle.GetLifetime() > m_lifetime)
		{
			m_lifetime = particle.GetLifetime();
		}
	}
}

void ParticleGroup::Update()
{
	if(m_isBeingUsed)
	{
		UpdateParticles();
	}
	ValidateLifetime();
}

void ParticleGroup::UpdateParticles()
{
	for (auto& particle : m_particles)
	{
		if (particle.IsAlive())
		{
			particle.Update();
		}
		m_currentLifetime++;
	}
}

void ParticleGroup::Draw()
{
	if (m_isBeingUsed)
	{
		DrawParticles();
	}
}

void ParticleGroup::DrawParticles()
{
	for (auto& particle : m_particles)
	{
		if (particle.IsAlive())
		{
			particle.Draw();
		}
	}
}

void ParticleGroup::UpdateParticlePositions(int x, int y)
{
	ResetState();
	for (auto& particle : m_particles)
	{
		particle.ChangePosition(x, y);
	}
}

void ParticleGroup::ResetState()
{
	m_isBeingUsed = true;
	m_currentLifetime = 0;
	for (auto& particle : m_particles)
	{
		particle.ResetState();
	}
}


