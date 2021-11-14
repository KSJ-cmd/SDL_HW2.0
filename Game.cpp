#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<vector>
#include<list>
#include<memory>
//#include"Nation.h"

#include"Game.h"
#include"TextureManager.h"
#include"Player.h"
#include"Enemy.h"
#include"InputHandler.h"
#include"Ball.h"
#include"Map.h"
#include "Bullet.h"
#include"ScrollBG.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance()
{
	if (s_pInstance == 0) {
		s_pInstance = new Game();
	}
	return s_pInstance;
}

Game::Game()
{
	
}
Game::~Game() {
	m_bgObjects.clear();
	m_bgObjects.shrink_to_fit();

	m_gameObjects.clear();
	m_gameObjects.shrink_to_fit();
	std::cout << "Game end" << std::endl;
}
bool Game::Init(const char* title, int xpos, int ypos, int width, int height, int flags){
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    m_pWindow =SDL_CreateWindow(title, xpos,  ypos,  width,  height,  flags);
	if (m_pWindow != 0) {
		TTF_Init();

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		m_pFont = TTF_OpenFont("font/BMDOHYEON_ttf.ttf", 30);
		TextureManager::Instance()->load("Assets/animate-alpha.png", "animate", m_pRenderer);
		TextureManager::Instance()->load("images/bg_scroll.png", "BG_main", m_pRenderer);
		TextureManager::Instance()->load("images/Alive_place_0.png", "bullet", m_pRenderer);


		SDL_Color textColor = { 255,255,255 };
		TextureManager::Instance()->loadText("Test", "text_temp", m_pRenderer, m_pFont, textColor);
		m_gameObjects.push_back(new SDLGameObject(new LoaderParams(100, 100, 200, 100, "text_temp", "text_temp")));


		m_bgObjects.push_back(new Scroll(new LoaderParams(0, 0, 1600, 900, "BG_main","background")));
		m_bgObjects.push_back(new Scroll(new LoaderParams(1600, 0, 1600, 900, "BG_main", "background")));


		for (int i = 0; i < 20; i++) {
			m_mapObjects.push_back(new Map(new LoaderParams((0 + (80 * i)), 800, 80, 80, "","map")));
		}
		for (int i = 0; i < 5; i++) {
			m_mapObjects.push_back(new Map(new LoaderParams(600, (800-(i*50)), 80, 80, "", "map")));
		}
		m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate","player")));
		m_gameObjects.push_back(new Enemy(new LoaderParams(400, 400, 128, 82, "animate","enemy")));
		
		//Ball* ball = new Ball(new LoaderParams(400, 400, 128, 82, "animate","ball"));
		//ball->SetMoveStrategy(new MoveXY());
		//m_gameObjects.push_back(ball);
		//Ball* ball2 = new Ball(new LoaderParams(400, 400, 128, 82, "animate","ball"));
		////ball2->setTag("enemy");
		//ball2->SetDrawStrategy(new Angle());
		//m_gameObjects.push_back(ball2);


	}
    else{
      return false;
    }
  }
  else {
    return false;
  }
  m_bRunning = true;
  return true;
}

void Game::Update() {
	m_currentFrame = ((SDL_GetTicks() / 100) % 6);
	for (std::vector<GameObject*>::iterator iter = m_bgObjects.begin(); iter != m_bgObjects.end(); iter++) {
		(*iter)->update();
	}
	for (std::vector<GameObject*>::iterator iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++) {
		(*iter)->update();
	}
}

void Game::render() {
	SDL_RenderClear(m_pRenderer);
	
	for (std::vector<GameObject*>::iterator iter = m_bgObjects.begin(); iter != m_bgObjects.end(); iter++) {
		(*iter)->draw();
	}
	for (std::vector<SDLGameObject*>::iterator iter = m_mapObjects.begin(); iter != m_mapObjects.end(); iter++) {
		(*iter)->draw();
	}
	for (std::vector<GameObject*>::iterator iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++) {
		(*iter)->draw();
	}
	

	SDL_RenderPresent(m_pRenderer);
}

bool Game::running() {
	return m_bRunning;
}

void Game::handleEvents() {
	TheInputHandler::Instance()->update();
}

void Game::clean() {
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

SDL_Renderer* Game::getRenderer() const
{
	return m_pRenderer;
}

TTF_Font* Game::getFont() const
{
	return m_pFont;
}

 std::vector<GameObject*>& Game::getBgs() 
{
	return m_bgObjects;
}
const std::vector<GameObject*>& Game::getBgs() const
{
	return m_bgObjects;
}

 std::vector<GameObject*>& Game::getObjects() 
{
	return m_gameObjects;
}
const std::vector<GameObject*>& Game::getObjects() const
{
	return m_gameObjects;
}


 std::vector<SDLGameObject*>& Game::getMaps() 
{
	return m_mapObjects;
}
const std::vector<SDLGameObject*>& Game::getMaps() const
{
	return m_mapObjects;
}



