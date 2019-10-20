#include "pch.h"
#include "EventsHandler.h"
#include "Aliases.h"
#include "Enums.h"
#include "Constants.h"
#include "Game.h"
#include "IGrid.h"

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
			TryToSpawnColumns(game);
		}
	}
}
void EventsHandler::QuitGame(Game& game)
{
	game.QuitGame();
}

void EventsHandler::PlayerClickedWindow(SDL_Event& event, IGrid& grid)
{
	if (grid.IsBrickOnClickedPosition(event.button.x, event.button.y))
	{
		std::set<std::pair<uint, uint>> indexesToDelete;
		grid.FindSequenceInClick(indexesToDelete);
		if (indexesToDelete.size() > 1)
		{
			grid.DeleteSequence(indexesToDelete);
			grid.DeleteEmptyColumns();
			grid.UpdatePositionOfBricks();
		}
	}
}

void EventsHandler::TryToSpawnColumns(Game& game)
{
	if (game.Grid().CurrentNumberOfColumns() < Consts::NUM_MAX_COLUMNS)
	{
		SpawnColumn(game.Grid());
	}
	else
	{
		RestartGame(game);
	}
	UpdateGrid(game.Grid());
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

void EventsHandler::InitTimer()
{
	int s = 0;
	m_spawnNewColumnTimer = SDL_AddTimer(Consts::MS_BETWEEN_COLUMN_SPAWNS, PushSpawnColumnEvent, &s);
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
