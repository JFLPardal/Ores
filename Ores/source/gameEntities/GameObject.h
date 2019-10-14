#pragma once

#include "Aliases.h"
#include "Transform.h"

class GameObject
{
public:
	GameObject();
	GameObject(int x, int y);
	virtual ~GameObject();

	virtual void Draw() const;
	void Update();
	uint GetId() const { return m_id; }
	Transform GetTransform() const { return m_transform; }
	
protected:
	static uint m_nextId;
	uint m_id;
	Transform m_transform;
private:
	void NextID();
};
