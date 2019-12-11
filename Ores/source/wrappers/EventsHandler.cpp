#include "pch.h"
#include "EventsHandler.h"
#include "Aliases.h"
#include "Enums.h"
#include "Constants.h"
#include "Game.h"
#include "IGrid.h"
#include "ClickWindow.h"

EventsHandler::EventsHandler()
	:m_clickEvent(std::make_unique<ClickWindow>())
{
}


void EventsHandler::ProcessEvents(Game& game)
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			QuitGame(game);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			PlayerClickedWindow(event, game.Grid());
		}
		if (event.type == SDL_USEREVENT && event.user.code == UserEvent::SpawnColumn)
		{
			if (TryToSpawnColumns(game))
			{
				UpdateColumnSpawnTimer();
			}
		}
	}
}
void EventsHandler::QuitGame(Game& game)
{
	game.QuitGame();
}

void EventsHandler::PlayerClickedWindow(SDL_Event& event, IGrid& grid)
{
	m_clickEvent->PlayerClickedWindow(event, grid);
}

bool EventsHandler::TryToSpawnColumns(Game& game)
{
	if (game.Grid().CurrentNumberOfColumns() < Consts::NUM_MAX_COLUMNS)
	{
		SpawnColumn(game.Grid());
	}
	else
	{
		// TODO change this to game over and put this function inside of that game over
		RestartGame(game);
		return false;
	}
	UpdateGrid(game.Grid());
	return true;
}

void EventsHandler::SpawnColumn(IGrid& grid)
{
	grid.SpawnColumn();
}

void EventsHandler::RestartGame(Game& game)
{
	SDL_RemoveTimer(m_spawnNewColumnTimer);
	game.Grid().ClearGrid();
	game.InitGame();
}

void EventsHandler::UpdateGrid(IGrid& grid)
{
	grid.UpdatePositionOfBricks();
}

void EventsHandler::InitTimer(float secondsBetweenColumnsSpawns)
{
	int s = 0;
	m_currentSecondsBetweenColumnsSpawns = secondsBetweenColumnsSpawns;
	m_spawnNewColumnTimer = SDL_AddTimer(m_currentSecondsBetweenColumnsSpawns * 1000, PushSpawnColumnEvent, &s);
}

void EventsHandler::UpdateColumnSpawnTimer()
{
	int s = 0;
	SDL_RemoveTimer(m_spawnNewColumnTimer); // make sure the previous assigned function(if any) is replaced with new timer instead of adding to it
	m_currentSecondsBetweenColumnsSpawns = GetNextColumnSpawnTimer();
	m_spawnNewColumnTimer = SDL_AddTimer(m_currentSecondsBetweenColumnsSpawns * 1000, PushSpawnColumnEvent, &s);
}

float EventsHandler::GetNextColumnSpawnTimer() const
{
	return std::max(
			m_currentSecondsBetweenColumnsSpawns - Consts::DECREMENT_COLUMN_SPAWN_TIMER_SECS,
			Consts::MIN_SEC_BETWEEN_COLUMN_SPAWNS
	);
}

Uint32 PushSpawnColumnEvent(Uint32 msBetweenSpawns, void* params)
{
	SDL_UserEvent userEvent;
	userEvent.type = SDL_USEREVENT;
	userEvent.code = UserEvent::SpawnColumn;

	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user = userEvent;

	SDL_PushEvent(&event);
	return msBetweenSpawns;
}
