﻿#pragma once
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
	void InitTimer(float secondsBetweenColumnsSpawns);
	void RestartGame(Game& game);
	void QuitGame(Game& game);
private:
	void PlayerClickedWindow(SDL_Event& event, IGrid& grid);
	bool TryToSpawnColumns(Game& game);
	
	void SpawnColumn(IGrid& grid);
	void UpdateGrid(IGrid& grid);
	float GetNextColumnSpawnTimer() const;
private:
	uPtr<ITimer> m_ColumnSpawnTimer;
	uPtr<IClickEvent> m_clickEvent;
	float m_currentSecondsBetweenColumnsSpawns = -1; // TODO remove from this class
};
