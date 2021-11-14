
#include"Game.h"
#include"Map.h"

Map::Map(const LoaderParams* pParams)
	:SDLGameObject(pParams)
{
	
}

Map::~Map()
{
}

void Map::draw() {

	SDL_Rect tempRect = { static_cast<int>(m_position.getX()),static_cast<int>(m_position.getY()),m_width,m_height };
	SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(Game::Instance()->getRenderer(), &tempRect);
}