#pragma once
#include "Aliases.h"
#include "GameObject.h"
#include "TextureManager.h"

struct SDL_Window;
struct SDL_Texture;

void SDL_DestroyWindow(SDL_Window*);
void SDL_DestroyTexture(SDL_Texture*);

class Game
{
public:
	Game();

	bool IsRunning() const { return m_isRunning; };
	void Update();
	void Draw();
	void ProcessEvents();
	void Clean();

	auto GetTextureManager() { return m_textureManager.get(); }
private:
	void InitGame();
	void InitGameObjects();
private:
	bool m_isRunning = true;
	uPtr<TextureManager> m_textureManager;
	uPtr<GameObject> m_go;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
};

