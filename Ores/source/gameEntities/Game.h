#pragma once
#include "Aliases.h"
#include "Brick.h"
#include "EventsHandler.h"

struct SDL_Window;
class IGrid;
class EventsHandler;
void SDL_DestroyWindow(SDL_Window*);

class Game
{
public:
	Game();
	~Game();

	bool IsRunning() const { return m_isRunning; };
	void Update();
	void Draw();
	void ProcessEvents();
	IGrid& Grid() const { return *m_grid.get(); }
	friend void EventsHandler::RestartGame(Game& game);
	friend void EventsHandler::QuitGame(Game& game);
private:
	void QuitGame() { m_isRunning = false; }
	void CreateWindow();
	void InitGame();
	void InitGameObjects();
private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	bool m_isRunning = true;
	GameObject m_warningArea;
	uPtr<IGrid> m_grid;
	uPtr<EventsHandler> m_eventsHandler;
};

