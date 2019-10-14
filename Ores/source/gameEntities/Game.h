#pragma once
#include "Aliases.h"
#include "GameObject.h"
#include "TextureManager.h"

struct SDL_Window;

void SDL_DestroyWindow(SDL_Window*);

class Game
{
public:
	Game();

	bool IsRunning() const { return m_isRunning; };
	void Update();
	void Draw();
	void ProcessEvents();
	void Clean();

	TextureManager* GetTextureManager() { return m_textureManager.get(); }
private:
	void InitGame();
	void InitGameObjects();
private:
	bool m_isRunning = true;
	uPtr<TextureManager> m_textureManager;
	uPtr<GameObject> m_go;
	uPtr<GameObject> m_go2;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
};

