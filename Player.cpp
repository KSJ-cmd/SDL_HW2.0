#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include "SDLGameObject.h"
#include"Game.h"
#include "InputHandler.h"
#include "Bullet.h"

Player::Player(const LoaderParams* pParams)
    :SDLGameObject(pParams) {

    setState(std::move(ButtonUp::Instance()));
}
  void Player::draw() {
      SDLGameObject::draw();
      for (std::list<GameObject*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
          (*iter)->draw();
      }
  }
   void Player::update() {
       handleInput();
       for (std::list<GameObject*>::iterator iter = m_bullets.begin(); iter != m_bullets.end(); iter++) {
           (*iter)->update();
       }

       m_currentFrame = ((SDL_GetTicks() / 100) % 6);

       std::cout << "m_velocity : " << m_velocity.getX() << " ," << m_velocity.getY() << std::endl;
       std::cout << "m_acceleration : " << m_acceleration.getX() << " ," << m_acceleration.getY() << std::endl;
       std::cout << "Jump : " << isJump << std::endl;
       SDLGameObject::update();
       Gravity();
       std::vector<SDLGameObject*> maps = Game::Instance()->getMaps();
       for (std::vector<SDLGameObject*>::iterator iter = maps.begin();
           iter != maps.end(); iter++) {
           if (  check_collision_camera() || check_collision(*this, **iter)) {
               isJump = false;
               m_acceleration.setY(0);
           }
           move(**iter);
       }
       
       std::cout << "m_velocity : " << m_velocity.getX() << " ," << m_velocity.getY() << std::endl;
       std::cout << "m_acceleration : " << m_acceleration.getX() << " ," << m_acceleration.getY() << std::endl;
       std::cout << "Jump : " << isJump << std::endl;
   }
   void Player::clean(){}
   
   void Player::handleInput() {
       if (!TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) &&
           !TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
           m_velocity.setX(0);
       }

       if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D)) {
           std::cout << "Right" << std::endl;
           m_velocity.setX(5);
       }
       
       if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_A)) {
           std::cout << "Left" << std::endl;
           m_velocity.setX(-5);
       }

      /* if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_W)) {
           std::cout << "A" << std::endl;
           CreateBullet();
       }*/
       
      /* if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
           std::cout << "Down" << std::endl;
           m_velocity.setY(2);
       }*/

       if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE)) {
           std::cout << "JUMP" << std::endl;
           isJump = true;
           m_acceleration.setY(-0.5);
       }
       if (TheInputHandler::Instance()->getMouseButtonState(0) && isClick == false) {
           std::cout << "shoot" << std::endl;
           isClick = true;
           Click();
           //m_bullets.push_back(new Bullet(new LoaderParams((int)m_position.getX(), (int)m_position.getY(), 31, 30, "bullet")));
           
       }
       if (!TheInputHandler::Instance()->getMouseButtonState(0) && isClick == true) {
           isClick = false;
           Click();
       }
   }
   void Player::CreateBullet()
   {
       m_bullets.push_back(new Bullet(new LoaderParams(static_cast<int>(m_position.getX()), static_cast<int>(m_position.getY()), 31, 30, "bullet","bullet")));
   }

   void Player::setState(std::shared_ptr<MouseState> MouseState)
   {  
       m_pMouseState = std::move(MouseState);
   }

   void Player::Click()
   {
       m_pMouseState.get()->Click(this);
   }

   void Player::Gravity()
   {
       m_acceleration.setY(m_acceleration.getY() + 0.1);

       //정지, 점프 최고점
       if (m_velocity.getX() < 0) {
           //점프후 최고점 도달
           if (m_acceleration.getY() <= 0) {
               m_acceleration.setY(0.3);
               isJump = false;
           }
           //점프후 중력에 의한 감속
           else if (m_acceleration.getY() < 0) {
               m_acceleration.setY(m_acceleration.getY() + 0.2);
           }
       }
   }

   std::shared_ptr<ButtonDown> ButtonDown::s_pInstance = nullptr;
   void ButtonDown::Click(Player* ButtonState)
   {
       std::cout << "ButtonDown" << std::endl;
       
       ButtonState->CreateBullet();

       std::shared_ptr<MouseState> pM(ButtonUp::Instance());
       ButtonState->setState(std::move(pM));
   }

   std::shared_ptr<ButtonUp> ButtonUp::s_pInstance = nullptr;
   void ButtonUp::Click(Player* ButtonState)
   {
       std::cout << "ButtonUp" << std::endl;

       std::shared_ptr<MouseState> pM(ButtonDown::Instance());
       ButtonState->setState(std::move(pM));
   }
