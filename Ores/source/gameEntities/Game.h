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
	void Update();
	void Draw();
	void ProcessEvents();
private:
	void CreateWindow();
	void InitGame();
	void InitGrid();
	void InitGameObjects();
	void InitBricks();

	std::pair<int, int> GetBrickRelativePosition(std::pair<uint, uint> brickPositionInGrid, Direction direction) const;
	std::pair<int, int> GridPositionOfBrick(const Brick& brick) const;

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
	GameObject m_warningArea;
	// grid operation
	std::vector<std::vector<Brick>> m_bricks;
	uint m_currentNumColumns;
	// event related
	Brick m_clickedBrick;
	SDL_TimerID m_spawnNewColumnTimer;
};

