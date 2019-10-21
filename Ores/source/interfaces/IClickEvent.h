#pragma once

class IGrid;
union SDL_Event;

class IClickEvent
{
public:
	virtual ~IClickEvent() = default;
	virtual void PlayerClickedWindow(SDL_Event& event, IGrid& grid) = 0;
};
