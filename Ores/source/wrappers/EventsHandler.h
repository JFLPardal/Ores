#pragma once
#include "IClickEvent.h"
#include "Aliases.h"
#include "ITimer.h"

class Game;
class IGrid;

Uint32 PushSpawnColumnEvent(Uint32 msBetweenSpawns, void* params);

class EventsHandler
{
public:
	EventsHandler();

	void ProcessEvents(Game& game);
	void RestartGame(Game& game);
	void QuitGame(Game& game);
private:
	void PlayerClickedWindow(SDL_Event& event, IGrid& grid);
	bool TryToSpawnColumns(Game& game);
	
	void SpawnColumn(IGrid& grid);
	void UpdateGrid(IGrid& grid);
private:
	uPtr<IClickEvent> m_clickEvent;
	
};
