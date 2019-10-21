#pragma once
#include "Enums.h"

class ParticleGroup;

class ParticleSystemManager
{
public:
	~ParticleSystemManager() = default;
	static void Init();
	
	static void FireParticles(ParticleType eventToFire, int x, int y);
	static void Update();
	static void Draw();
private:
	static void ClickOnBrick(int x, int y);
private:
	static ParticleGroup m_clickedBrickParticles;
};
