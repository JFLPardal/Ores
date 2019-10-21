﻿#pragma once
#include "IClickEvent.h"
#include "Aliases.h"

class Game;
class IGrid;

Uint32 PushSpawnColumnEvent(Uint32 msBetweenSpawns, void* params);

class EventsHandler
{
public:
	EventsHandler();

	void ProcessEvents(Game& game);
	void InitTimer();
	void RestartGame(Game& game);
	void QuitGame(Game& game);
private:
	void PlayerClickedWindow(SDL_Event& event, IGrid& grid);
	void TryToSpawnColumns(Game& game);
	
	void SpawnColumn(IGrid& grid);
	void UpdateGrid(IGrid& grid);
private:
	SDL_TimerID m_spawnNewColumnTimer;
	uPtr<IClickEvent> m_clickEvent;
};
