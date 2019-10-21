#include "pch.h"
#include "ParticleSystemManager.h"
#include "ParticleGroup.h"

ParticleGroup ParticleSystemManager::m_clickedBrickParticles;

void ParticleSystemManager::Init()
{
	m_clickedBrickParticles = ParticleGroup();
}

void ParticleSystemManager::FireParticles(ParticleType eventToFire, int x, int y)
{
	switch (eventToFire)
	{
	case clickOnBrick:
		ClickOnBrick(x, y);
		break;
	case clickOnVoid:
		break;
	}
}

void ParticleSystemManager::ClickOnBrick(int x, int y)
{
	m_clickedBrickParticles.UpdateParticlePositions(x, y);
}

void ParticleSystemManager::Update()
{
	if(m_clickedBrickParticles.IsBeingUsed())
	{
		m_clickedBrickParticles.Update();
	}
}

void ParticleSystemManager::Draw()
{
	if(m_clickedBrickParticles.IsBeingUsed())
	{
		m_clickedBrickParticles.Draw();
	}
}


