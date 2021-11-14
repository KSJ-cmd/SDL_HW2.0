#ifndef __BULLET_H__
#define __BULLET_H__

#include"SDLGameObject.h"

class Bullet : public SDLGameObject{
public:
  Bullet(const LoaderParams* pParams);
  virtual void draw();
  virtual void update();
  virtual void clean() {}
private:

};

#endif