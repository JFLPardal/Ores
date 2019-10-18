#include "Constants.h"

namespace Consts
{
	// frame rate
	const int INTENDED_FPS = 60;
	const int INTENDED_FRAME_DURATION = 1000 / INTENDED_FPS;

	// window
	const int WINDOW_HEIGHT = 480;
	const int WINDOW_WIDTH = 640;
	const char* WINDOW_NAME = "Ores by Joao Pardal";

	// sprites
	const char* blueOre = "../Ores/assets/sprites/ores/blue_square.png";
	const char* redOre = "../Ores/assets/sprites/ores/red_square.png";
	const char* greenOre = "../Ores/assets/sprites/ores/green_square.png";

	//
	const unsigned int NUM_DIF_BRICKS = 5;
	
	// sprites' dimensions
	const unsigned int BRICK_W = 32;
	const unsigned int BRICK_H = 32;

	// grid's dimensions
	const unsigned int BRICKS_PER_COLUMN = 10;
	const unsigned int NUM_MAX_COLUMNS = 5;
	const unsigned int NUM_INITIAL_COLUMNS = 3;
	const unsigned int INITIAL_VEC_CAPACITY = BRICKS_PER_COLUMN * NUM_INITIAL_COLUMNS;

	// initial brick's position
	const unsigned int INITIAL_BRICK_X = WINDOW_WIDTH - BRICK_W;
	const unsigned int INITIAL_BRICK_Y = WINDOW_HEIGHT * 0.5f - BRICK_H * BRICKS_PER_COLUMN * 0.5f;

	// directions
	const unsigned int NUM_DIRECTIONS = 4;
}
	
