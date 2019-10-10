#include "pch.h"

#include "Game.h"
#include "Constants.h"

void EnforceFrameRate(const Uint32 frameStart);

int main(int argc, char* argv[])
{
	auto m_game = std::make_unique<Game>();
	Uint32 frameStart = 0;
	
	while(m_game->IsRunning())
	{
		frameStart = SDL_GetTicks();
		m_game->ProcessEvents();
		m_game->Update();
		m_game->Draw();
		EnforceFrameRate(frameStart);
	}
	m_game->Clean();
	return 0;
}

void EnforceFrameRate(const Uint32 frameStart)
{
	Uint32 const frameDuration = SDL_GetTicks() - frameStart;
	Uint16 const intendedFrameDuration = Consts::INTENDED_FRAME_DURATION;
	if (intendedFrameDuration > frameDuration)
	{
		SDL_Delay(intendedFrameDuration - frameDuration);
	}
}

