#pragma once
#ifndef __TEXTURE_MANAGER__
#define __TEXTURE_MANAGER__
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<string>
#include<map>

class TextureManager
{
public:
	TextureManager() = default;
	~TextureManager()= default;
	static TextureManager* Instance();
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	bool loadText(std::string text, std::string id, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor);
	void draw(std::string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(std::string id, int x, int y, int width, int height,
		int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawAngle(std::string id, int x, int y, int width, int height,
		int currentRow, int currentFrame, int angle, 
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	static TextureManager* s_pInstance;
};


#endif // !__TEXTURE_MANAGER__
