#pragma once
#include "Aliases.h"
#include "Brick.h"

struct SDL_Window;
class IGrid;
void SDL_DestroyWindow(SDL_Window*);

Uint32 PushSpawnColumnEvent(Uint32 msBetweenSpawns, void* params);

class Game
{
public:
	Game();
	~Game();

	bool IsRunning() const { return m_isRunning; };
	void Update();
	void Draw();
	void ProcessEvents();
private:
	void CreateWindow();
	void InitGame();
	void InitGameObjects();

	void InitTimer();
private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	bool m_isRunning = true;
	GameObject m_warningArea;
	uPtr<IGrid> m_grid; 
	// event related
	Brick m_clickedBrick;
	SDL_TimerID m_spawnNewColumnTimer;
};

