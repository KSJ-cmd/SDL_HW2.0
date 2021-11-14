#include"ScrollBG.h"

Scroll::Scroll(const LoaderParams* pParams)
	:SDLGameObject(pParams)
{
	m_velocity.setX(-1);
}

void Scroll::draw()
{
	SDLGameObject::draw();
	if (m_position.getX() + m_width <= 0) {
		m_position.setX(1599);
	}
}

void Scroll::update()
{
	SDLGameObject::update();
	
}

void Scroll::clean()
{
}
