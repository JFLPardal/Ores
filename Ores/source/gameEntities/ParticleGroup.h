#pragma once
#include "Aliases.h"
#include "Particle.h"
//class Particle;

class ParticleGroup
{
public:
	ParticleGroup();

	void Update();
	void Draw();
	
	void UpdateParticlePositions(int x, int y);
	bool IsBeingUsed() const { return m_isBeingUsed; }
	void ValidateLifetime() { m_isBeingUsed = (m_currentLifetime > m_lifetime) ? false : true; }
private:
	void UpdateParticles();
	void DrawParticles();
	void ResetState();
private:
	bool m_isBeingUsed = false;
	uint m_lifetime;
	uint m_currentLifetime = 0;
	std::vector<Particle> m_particles;
};