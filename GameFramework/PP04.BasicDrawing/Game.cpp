#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow != 0)
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}

		m_bRunning = true;
		SDL_Surface* pTempSurface = SDL_LoadBMP("Assets/rider.bmp");
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);

		SDL_FreeSurface(pTempSurface);

		SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
	}
	else
	{
		return false;	// sdl could not initialize
	}

	

	return true;
}

void Game::render()
{
	m_destinationRectangle.x = m_sourceRectangle.x = 0;
	m_destinationRectangle.y = m_sourceRectangle.y = 0;	

	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;
	
	m_sourceRectangle.x = 61;
	m_sourceRectangle.y = 43;

	m_destinationRectangle.x = 100;
	m_destinationRectangle.y = 100;

	// clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);	// draw color로 render 지우기

	// 원본 사각형과 대상 사각형의 위치와 크기에 따라 화면에 다르게 나타남...
	SDL_RenderCopy(m_pRenderer, m_pTexture,
					&m_sourceRectangle, &m_destinationRectangle);

	SDL_RenderPresent(m_pRenderer);	// 화면 제시하기
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}