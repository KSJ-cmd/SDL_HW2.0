#include<iostream>
#include"TextureManager.h"
#include"Game.h"
#include"GameObject.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

SDLGameObject::SDLGameObject(const LoaderParams* pParams)
    :GameObject(pParams)
    , m_position(pParams->getX(), pParams->getY())
    , m_velocity(0, 0)
    , m_acceleration(0, 0)
    , isActive(true)    
{
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_tag = pParams->getTag();
    m_currentRow = 0;
    m_currentFrame = 0;
}
void SDLGameObject::update() {

    m_velocity += m_acceleration;
    m_position += m_velocity;
}
void SDLGameObject::draw(){
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, Game::Instance()->getRenderer());
}


void SDLGameObject::move(SDLGameObject& wall)
{
    if ((m_position.getX() < 0) || (m_position.getX() + m_width > SCREEN_WIDTH) || check_collision(*this, wall)) {
        m_position.setX(m_position.getX() - m_velocity.getX());
        m_velocity.setX(0);
    }
    if ((m_position.getY() < 0) || (m_position.getY() + m_width > SCREEN_HEIGHT) || check_collision(*this, wall)) {
        m_position.setY(m_position.getY() - m_velocity.getY());
        m_velocity.setY(0);
        
    }
}

std::string SDLGameObject::getTag() const
{
    return m_tag;
}

bool SDLGameObject::getActive() const
{
    return isActive;
}

void SDLGameObject::Active()
{
    isActive = true;
}

void SDLGameObject::InActive()
{
    isActive = false;
}

bool SDLGameObject::check_collision(SDLGameObject& A, SDLGameObject& B)
{
    if (check_collision_X(A, B) && check_collision_Y(A, B))
        return true;
    else
        return false;
}

bool SDLGameObject::check_collision_X(SDLGameObject& A, SDLGameObject& B)
{
    int leftA, leftB;
    int rightA, rightB;

    leftA = A.m_position.getX();
    rightA = A.m_position.getX() + A.m_width;

    leftB = B.m_position.getX();
    rightB = B.m_position.getX() + B.m_width;

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    return true;
}

bool SDLGameObject::check_collision_Y(SDLGameObject& A, SDLGameObject& B)
{
    int topA, topB;
    int bottomA, bottomB;

    topA = A.m_position.getY();
    bottomA = A.m_position.getY() + A.m_height;

    topB = B.m_position.getY();
    bottomB = B.m_position.getY() + B.m_height;

    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }


    return true;
}

bool SDLGameObject::check_collision_camera()
{
    if ((m_position.getX() < 0) || (m_position.getX() + m_width > SCREEN_WIDTH)) {
        return true;
    }
    if ((m_position.getY() < 0) || (m_position.getY() + m_width > SCREEN_HEIGHT)) {
        return true;
    }
    return false;
}
