#pragma once
#include "pch.h" // <memory> and <SDL.h>

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
	void CreateRenderer();
	void LoadTexture(const char* spritePath);
private:
	bool m_isRunning = true;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_textureToDelete;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;
};

