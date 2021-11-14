#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include<vector>
#include"TextureManager.h"
#include"GameObject.h"
#include"Player.h"

class Game {
public:
static Game* Instance();
	~Game();

  bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void Update();
	bool running();
	void handleEvents();
	void clean();

	void quit() { m_bRunning = false; }
	SDL_Renderer* getRenderer() const;
	TTF_Font* getFont() const;

	 std::vector<GameObject*>& getBgs() ;
	const std::vector<GameObject*>& getBgs() const;

	 std::vector<SDLGameObject*>& getMaps() ;
	const std::vector<SDLGameObject*>& getMaps() const;

	 std::vector<GameObject*>& getObjects() ;
	const std::vector<GameObject*>& getObjects() const;

private:
	Game();
  static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	TTF_Font* m_pFont;
	bool m_bRunning;

	int m_currentFrame;

	std::vector<GameObject*> m_bgObjects;
	std::vector<SDLGameObject*> m_mapObjects;
	std::vector<GameObject*> m_gameObjects;

};
#endif // !__GAME_H__