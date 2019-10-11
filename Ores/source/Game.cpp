#include "Game.h"

#include "TextureManager.h"
#include "Constants.h"
#include "GameObject.h"

Game::Game()
	:m_textureManager(nullptr), m_window(nullptr, SDL_DestroyWindow),
	m_textureToDelete(nullptr, SDL_DestroyTexture)
{
	Init();
	//m_textureManager = std::make_unique<TextureManager>(m_window.get());
	m_textureManager = new TextureManager(m_window.get());
}

void Game::Init()
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
	// texture loading 
	const char* imagePath = "../Ores/assets/sprites/paddle.png";
	//LoadTexture(imagePath);

	// create game object
	m_go = std::make_unique<GameObject>();
}

void Game::Draw()
{
	m_textureManager->ClearRender();
	m_go->Draw();
	m_textureManager->PresentRender();
}

void Game::Update()
{
	m_go->Update();
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
	}
}

void Game::Clean()
{
	SDL_Quit();
}

