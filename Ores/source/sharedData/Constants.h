#pragma once

namespace Consts
{
	// frame rate
	extern const int INTENDED_FPS;
	extern const int INTENDED_FRAME_DURATION;

	// window
	extern const int WINDOW_HEIGHT;
	extern const int WINDOW_WIDTH;
	extern const char* WINDOW_NAME;
	
	// sprites' path
	extern const char* blueOre;
	extern const char* redOre;
	extern const char* greenOre;
	extern const char* greyOre;
	extern const char* yellowOre;

	// 
	extern const unsigned int NUM_DIF_BRICKS;
	
	// sprites' dimensions
	extern const unsigned int BRICK_W;
	extern const unsigned int BRICK_H;

	// grid's dimensions
	extern const unsigned int BRICKS_PER_COLUMN;
	extern const unsigned int NUM_MAX_COLUMNS;
	extern const unsigned int NUM_INITIAL_COLUMNS;
	extern const unsigned int INITIAL_VEC_CAPACITY;

	// loosing warning
	extern const unsigned int LOSING_WARNING_X;
	extern const unsigned int LOSING_WARNING_Y;
	extern const unsigned int LOSING_WARNING_W;
	extern const unsigned int LOSING_WARNING_H;
	
	// initial brick's position
	extern const int INITIAL_BRICK_X;
	extern const int INITIAL_BRICK_Y;

	// directions
	extern const unsigned int NUM_DIRECTIONS;

	// delays (all in ms)
	extern const unsigned int MS_BETWEEN_COLUMN_SPAWNS;
}


