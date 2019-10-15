#include "pch.h"
#include "Game.h"

#include "Constants.h"
#include "TextureManager.h"
#include "Brick.h"

Game::Game()
	:m_window(nullptr, SDL_DestroyWindow)
{
	m_bricks.reserve(Consts::INITIAL_VEC_CAPACITY); // TODO change this, it will resize after the first iteration
	InitGame();
	m_textureManager = std::make_unique<TextureManager>(m_window.get());
	InitGameObjects();
}

void Game::InitGame()
{
	if (SDL_Init(SDL_INIT_VIDEO) != -1)
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
										Consts::WINDOW_WIDTH, Consts::WINDOW_HEIGHT, SDL_WINDOW_SHOWN));
	}
	else
	{
		printf("%s", SDL_GetError());
	}
}
void Game::InitGameObjects()
{
	m_bricks.emplace_back(std::make_unique<Brick>()); // construct brick on the vertex with these params (saves copies)
	m_bricks.emplace_back(std::make_unique<Brick>(150,150));
}

void Game::Draw()
{
	m_textureManager->ClearRender();
	for(auto& brick : m_bricks)
	{
		brick->Draw();
	}
	m_textureManager->PresentRender();
}

void Game::Update()
{
	for (auto& brick : m_bricks)
	{
		brick->Update();
	}
}

void Game::ProcessEvents()
{
	auto event = std::make_unique<SDL_Event>();
	while(SDL_PollEvent(event.get()) != 0)
	{
		if(event->type == SDL_QUIT)
		{
			m_isRunning = false;
		}
		else if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT)
		{
			printf("button click: x: %d y: %d\n", event->button.x, event->button.y);
			if(IsBrickOnClickedPosition(event->button.x, event->button.y))
			{
				// process click
				printf("cliked on a brick %d , %d\n", m_clickedBrick.GetTransform().X(), m_clickedBrick.GetTransform().Y());
			}
		}
	}
}

bool Game::IsBrickOnClickedPosition(int x, int y)
{
	SDL_Point positionClicked{x, y};
	for(auto& brick : m_bricks)
	{
		if(SDL_PointInRect(&positionClicked, &brick->GetTransform().Rect()))
		{
			m_clickedBrick = *brick;
			return true;
		}
	}
	return false;
}

void Game::Clean()
{
	SDL_Quit();
}

Game::~Game()
{
	Clean();
}


