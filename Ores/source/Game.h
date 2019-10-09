#pragma once

#include <memory>
#include "SDL.h"

class Game
{
public:
	Game();

	bool IsRunning() const { return m_isRunning; };
	void Update();
	void Draw();
	void ProcessEvents();
	void Clean();
private:
	void Init();
private:
	bool m_isRunning = true;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{ nullptr, SDL_DestroyWindow };
};

