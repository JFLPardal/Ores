﻿#include "pch.h"
#include "EventsHandler.h"
#include "Aliases.h"
#include "Enums.h"
#include "Constants.h"
#include "Game.h"
#include "IGrid.h"
#include "ClickWindow.h"
#include "TimerWithFillBar.h"

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
				game.ChangeSecondsBetweenColumnSpawns();
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
	bool spawnedColumn = false;
	if (game.Grid().CurrentNumberOfColumns() < Consts::NUM_MAX_COLUMNS)
	{
		SpawnColumn(game.Grid());
		spawnedColumn = true;
	}
	else
	{
		// TODO change this to game over and put this function inside of that game over
		RestartGame(game);
	}
	UpdateGrid(game.Grid());
	return spawnedColumn;
}

void EventsHandler::SpawnColumn(IGrid& grid)
{
	grid.SpawnColumn();
}

void EventsHandler::RestartGame(Game& game)
{
	game.Grid().ClearGrid();
	game.InitGame();
}

void EventsHandler::UpdateGrid(IGrid& grid)
{
	grid.UpdatePositionOfBricks();
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
