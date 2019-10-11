#pragma once
#include "pch.h" // <memory> and <SDL.h> TODO move the pch.h to .cpp
#include "Aliases.h"
#include "GameObject.h"

class TextureManager;

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
	std::unique_ptr<GameObject> m_go; // TODO change all these to uPtr
	TextureManager* m_textureManager;
	//uPtr<TextureManager> m_textureManager;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_textureToDelete;
};

