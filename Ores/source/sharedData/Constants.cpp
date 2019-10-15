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
	const char* imagePath = "../Ores/assets/sprites/ores/blue.png";

	// sprites' dimensions
	const unsigned int BRICK_W = 64;
	const unsigned int BRICK_H = 64;

	// grid's dimensions
	const unsigned int BRICKS_PER_COLUMN = 10;
	const unsigned int NUM_MAX_COLUMNS = 10;
	const unsigned int NUM_INITIAL_COLUMNS = 3;
	const unsigned int INITIAL_VEC_CAPACITY = BRICKS_PER_COLUMN * NUM_INITIAL_COLUMNS;
}
	
