#include<iostream>
#include<SDL.h>
#include"Enemy.h"
#include"InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams)
  :SDLGameObject(pParams){}
void Enemy::draw() {
    if (isActive == true) {
        SDLGameObject::draw();
    }
}
void Enemy::update(){
    if (isActive == true) {
        handleInput();
        m_currentFrame = ((SDL_GetTicks() / 100) % 6);
        // m_acceleration.setX(0.1);
        SDLGameObject::update();
    }
}
void Enemy::clean(){}

Enemy::~Enemy()
{
}

void Enemy::handleInput(){
    /* if(TheInputHandler::Instance()->getMouseButtonState(0)){
       std::cout<<"shoot"<<std::endl;
     }*/
     Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
     m_velocity = (*vec - m_position)/10;
   }