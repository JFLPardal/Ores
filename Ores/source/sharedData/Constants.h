#pragma once

namespace Consts
{
	// frame rate
	extern const int INTENDED_FPS;
	extern const int INTENDED_FRAME_DURATION;
	extern const float FRAME_DURATION_IN_MS;

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
	extern const char* brickParticle;

	// 
	extern const unsigned int NUM_DIF_BRICKS;

	// default game objects' dimensions
	extern const unsigned int DEFAULT_W;
	extern const unsigned int DEFAULT_H;
	
	// sprites' dimensions
	extern const unsigned int BRICK_W;
	extern const unsigned int BRICK_H;

	// grid's dimensions
	extern const unsigned int BRICKS_PER_COLUMN;
	extern const unsigned int NUM_MAX_COLUMNS;
	extern const unsigned int NUM_INITIAL_COLUMNS;
	extern const unsigned int INITIAL_VEC_CAPACITY;

	// particles 
	extern const unsigned int MAX_PARTICLE_LIFETIME; // in frames, should be ms
	extern const unsigned int MIN_PARTICLE_LIFETIME; // in frames, should be ms
	extern const unsigned int MIN_NUMBER_PARTICLES; 
	extern const unsigned int MAX_NUMBER_PARTICLES; 
	
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

	// delays (all in s)
	extern const float SEC_BETWEEN_COLUMN_SPAWNS;
	extern const float MIN_SEC_BETWEEN_COLUMN_SPAWNS;
	extern const float DECREMENT_COLUMN_SPAWN_TIMER_SECS;

	// 
	extern const float USE_ALREADY_SET_SECS;

	// UI Bar dimension
	extern const unsigned int UI_BAR_W;
	extern const unsigned int UI_BAR_H;
	
	// Timer UIBar position
	extern const unsigned int UI_BAR_X;
	extern const unsigned int UI_BAR_Y;
}


