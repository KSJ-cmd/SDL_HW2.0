#include"TextureManager.h"
#include<SDL.h>
#include<SDL_image.h>
//#include<SDL_ttf.h>
#include<utility>

TextureManager* TextureManager::s_pInstance = 0;

TextureManager* TextureManager::Instance()
{
	if (s_pInstance == 0) {
		s_pInstance = new TextureManager();
	}
	return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

		if (pTempSurface == NULL) {
			printf("%s\n", IMG_GetError());
		return false;
		}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}

bool TextureManager::loadText(std::string text, std::string id, SDL_Renderer* pRenderer, TTF_Font* pFont, SDL_Color textColor = {0,0,0})
{
	SDL_Surface* pTempSurface = TTF_RenderText_Solid(pFont,text.c_str(),textColor);

	if (pTempSurface == NULL) {
		printf("%s\n", TTF_GetError());
		std::cout << "error ttf" << std::endl;
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}
void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,  int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);

}
void TextureManager::drawAngle(std::string id, int x, int y, int width, int height, int angle, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);

}

