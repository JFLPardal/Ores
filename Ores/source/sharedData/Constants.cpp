#include "Constants.h"

namespace Consts
{
	// frame rate
	const int INTENDED_FPS = 60;
	const int INTENDED_FRAME_DURATION = 1000 / INTENDED_FPS;
	const float FRAME_DURATION_IN_MS = .0166f; // 1 / 60

	// window
	const int WINDOW_HEIGHT = 480;
	const int WINDOW_WIDTH = 640;
	const char* WINDOW_NAME = "Ores by Joao Pardal";

	// sprites
	const char* blueOre = "../Ores/assets/sprites/ores/blue_square.png";
	const char* redOre = "../Ores/assets/sprites/ores/red_square.png";
	const char* greenOre = "../Ores/assets/sprites/ores/green_square.png";
	const char* greyOre = "../Ores/assets/sprites/ores/grey_square.png";
	const char* yellowOre = "../Ores/assets/sprites/ores/yellow_square.png";
	const char* brickParticle = "../Ores/assets/sprites/ores/brick_particle.png";

	//
	const unsigned int NUM_DIF_BRICKS = 5;

	// default game objects' dimensions
	const unsigned int DEFAULT_W = 10;
	const unsigned int DEFAULT_H = 10;
	
	// sprites' dimensions
	const unsigned int BRICK_W = 32;
	const unsigned int BRICK_H = 32;

	// grid's dimensions
	const unsigned int BRICKS_PER_COLUMN = 10;
	const unsigned int NUM_MAX_COLUMNS = 16;
	const unsigned int NUM_INITIAL_COLUMNS = 5;
	const unsigned int INITIAL_VEC_CAPACITY = BRICKS_PER_COLUMN * NUM_INITIAL_COLUMNS;

	// initial brick's position
	const int INITIAL_BRICK_X = WINDOW_WIDTH - BRICK_W;
	const int INITIAL_BRICK_Y = (int)(WINDOW_HEIGHT * 0.5f) + (int)(BRICK_H * BRICKS_PER_COLUMN * 0.5f);

	// particles 
	const unsigned int MAX_PARTICLE_LIFETIME = 25; // in frames, should be ms
	const unsigned int MIN_PARTICLE_LIFETIME = 20; // in frames, should be ms
	const unsigned int MIN_NUMBER_PARTICLES = 3;
	const unsigned int MAX_NUMBER_PARTICLES = 5;
	
	// loosing warning
	extern const unsigned int LOSING_WARNING_X = WINDOW_WIDTH - BRICK_W * NUM_MAX_COLUMNS - (int)(BRICK_W * 0.5f);
	extern const unsigned int LOSING_WARNING_Y = (int)(WINDOW_HEIGHT * 0.5f) - (int)(BRICK_H * BRICKS_PER_COLUMN * 0.5f);
	extern const unsigned int LOSING_WARNING_W = (int)(BRICK_W * 0.25f);
	extern const unsigned int LOSING_WARNING_H = BRICK_H * (BRICKS_PER_COLUMN + 2);

	// directions
	const unsigned int NUM_DIRECTIONS = 4;
	
	// delays (all in s)
	const float SEC_BETWEEN_COLUMN_SPAWNS = 4;
	const float MIN_SEC_BETWEEN_COLUMN_SPAWNS = 1;
	const float DECREMENT_COLUMN_SPAWN_TIMER_SECS = .5f; 
	
	//
	const float USE_ALREADY_SET_SECS = -1;

	// UI Bar dimension
	const unsigned int UI_BAR_W = 128;
	const unsigned int UI_BAR_H = 32;

	// Timer UIBar position
	const unsigned int UI_BAR_X = WINDOW_WIDTH * .5f - UI_BAR_W * .5f;
	const unsigned int UI_BAR_Y = 0;
}
	
