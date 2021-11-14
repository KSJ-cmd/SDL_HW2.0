#include "Ball.h"
#include"TextureManager.h"
#include"Game.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

void MoveY::Move(Ball& ball)
{
	ball.SetSpeed(0, 1);
}

void MoveX::Move(Ball& ball)
{
	ball.SetSpeed(1, 0);
}

void MoveXY::Move(Ball& ball)
{
	ball.SetSpeed(1, 1);
}


Ball::Ball(const LoaderParams* pParams)
	: SDLGameObject(pParams) {}


Ball::~Ball()
{
	delete moveStrategy;
	delete drawStrategy;
}

//Ball::Ball(const Ball& src)
//	:SDLGameObject(src.)
//{
//
//}

void Ball::Move()
{
	moveStrategy->Move(*this);
}

void Ball::SetSpeed(int x, int y)
{
	xSpeed = x;
	ySpeed = y;
}

void Ball::Collision()
{
	if (m_position.getX() < 0 && xSpeed<0 || (m_position.getX() +m_width)>SCREEN_WIDTH && xSpeed>0)
		xSpeed *= -1;
	if (m_position.getY() < 0 && ySpeed<0 || (m_position.getY() +m_height)>SCREEN_HEIGHT && ySpeed>0)
		ySpeed *= -1;
}

void Ball::SetMoveStrategy(MoveStrategy* MoveStrategy)
{
	moveStrategy = MoveStrategy;
	moveStrategy->Move(*this);
}

void Ball::SetDrawStrategy(DrawStrategy*DrawStrategy)
{
	drawStrategy = DrawStrategy;
	drawStrategy->Draw(*this);
}

void Ball::update()
{
	float x = m_position.getX();
	float y = m_position.getY();
	m_position.setX(x + (4 * xSpeed));
	m_position.setY(y + (4 * ySpeed));

	Collision();
}

void Ball::draw() {
	drawStrategy->Draw(*this);
}

void Ball::drawAngle()
{
	TextureManager::Instance()->drawAngle(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, angle++, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
}

void Frame::Draw(Ball& ball)
{
	ball.SDLGameObject::draw();
}

void Angle::Draw(Ball& ball)
{
	ball.drawAngle();
}
