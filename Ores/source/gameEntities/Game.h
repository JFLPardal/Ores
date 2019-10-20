#pragma once
#include "Aliases.h"
#include "Brick.h"

struct SDL_Window;
class TextureManager;
void SDL_DestroyWindow(SDL_Window*);

Uint32 PushSpawnColumnEvent(Uint32 msBetweenSpawns, void* params);

class Game
{
public:
	Game();
	~Game();

	bool IsRunning() const { return m_isRunning; };
	bool IsGameOver() const { return m_isGameOver; }
	void Update();
	void Draw();
	void ProcessEvents();
	void Clean();

	TextureManager* GetTextureManager() const { return m_textureManager.get(); }
private:
	void CreateWindow();
	void InitGame();
	void InitGrid();
	void InitGameObjects();
	void InitBricks();
	void GameOver() { m_isGameOver = true; }

	std::pair<int, int> GetBrickRelativePosition(std::pair<uint, uint> brickIndexInGrid, Direction direction)const;
	std::pair<int, int> GridPositionOfBrick(const Brick& brick) const;

	//uPtr<std::set<std::pair<size_t, size_t>>> FindSequenceStartingIn(const Brick& brick) const;
	void FindSequenceStartingIn(const Brick& brick, std::set<std::pair<uint, uint>>& indexesToDelete) const;
	void DeleteSequence(const std::set<std::pair<uint, uint>>& indexesToDelete);
	
	bool IsBrickOnClickedPosition(int x, int y);	// TODO make this more efficient
	bool IsPositionValid(std::pair<int, int> position) const;
	void UpdatePositionInGrid();
	void DeleteEmptyColumns();

	void InitTimer();
	void SpawnColumn();
	void InitBrickColumn(uint columnIndex);
private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
	bool m_isRunning = true;
	bool m_isGameOver = false;
	uPtr<TextureManager> m_textureManager;
	Brick m_clickedBrick;
	GameObject m_warningArea;
	uint m_currentNumColumns;
	SDL_TimerID m_spawnNewColumnTimer;
	std::vector<std::vector<Brick>> m_bricks;
};

