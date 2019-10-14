#pragma once

#include "Aliases.h"

using uint = unsigned int;
class ISprite;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void Draw() const;
	void Update();
	inline uint GetId() const { return m_id; }
protected:
	static uint m_nextId;
	uint m_id;
	uPtr<ISprite> m_sprite;
};
