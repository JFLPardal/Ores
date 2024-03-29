#pragma once

#include "Aliases.h"
#include "Transform.h"

class GameObject
{
public:
	GameObject();
	GameObject(int x, int y);
	GameObject(int x, int y, int w, int h);
	virtual ~GameObject() = default;

	virtual void Draw() const;
	virtual void Update();
	uint GetId() const { return m_id; }
	const Transform& GetTransform() const { return m_transform; }
	
protected:
	static uint m_nextId;
	uint m_id;
	Transform m_transform;
private:
	void NextID();
};
