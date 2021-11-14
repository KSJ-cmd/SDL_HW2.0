#include"Bullet.h"
#include"InputHandler.h"
#include"Game.h"

Bullet::Bullet(const LoaderParams* pParams)
  :SDLGameObject(pParams){
    /*Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
     m_velocity = (*vec - m_position)/100;
     std::cout << m_velocity.getX()<<" , " << m_velocity.getY() << std::endl;*/
    m_velocity.setX(2);
}

void Bullet::draw(){
    if (isActive == true) {
        SDLGameObject::draw();
    }
}
void Bullet::update() {
    if (isActive == true) {
        SDLGameObject::update();

        std::vector<SDLGameObject*> maps = Game::Instance()->getMaps();
        for (std::vector<SDLGameObject*>::iterator iter = maps.begin();
            iter != maps.end(); iter++) {
            if (check_collision(*this, (**iter))) {
                InActive();
            }
        }
        if (check_collision_camera()) {
            InActive();
        }
        std::vector<GameObject*> targets = Game::Instance()->getObjects();
        for (std::vector<GameObject*>::iterator iter = targets.begin(); iter != targets.end(); iter++) {
            SDLGameObject* target = dynamic_cast<SDLGameObject*>(*iter);
            if (target->getTag() == "enemy") {
                if (check_collision(*this, *target)&&target->getActive()) {
                    target->InActive();
                    InActive();
                }
            }
        }
    }
}
