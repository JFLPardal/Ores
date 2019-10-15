#pragma once
#include "Aliases.h"
#include "Brick.h"

struct SDL_Window;
class TextureManager;
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
	void Clean();

	TextureManager* GetTextureManager() const { return m_textureManager.get(); }
private:
	void InitGame();
	void InitGameObjects();

	bool IsBrickOnClickedPosition(int x, int y);	// TODO make this more efficient
private:
	bool m_isRunning = true;
	uPtr<TextureManager> m_textureManager;
	Brick m_clickedBrick;
	std::vector<uPtr<Brick>> m_bricks;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
};

