#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
public:
	Particle();
	Particle(int x, int y);
	~Particle() = default;
	
	void Update() override;
	void Draw();
	bool IsAlive() const { return m_isAlive; }
	void ValidateLifetime() { m_isAlive = (m_currentLifetime > m_lifetime) ? false : true; }
	void ChangePosition(int x, int y);
	uint GetLifetime() const { return m_lifetime; }
	void ResetState();
private:
	void UpdatePosition();
private:
	bool m_isAlive = false;
	uint m_lifetime;
	uint m_currentLifetime = 0;
	std::pair<int, int> m_velocity;
	// add texture based on particleType
};
