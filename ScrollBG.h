#pragma once

#include"SDLGameObject.h"

class Scroll : public SDLGameObject {
public:
	Scroll(const LoaderParams* pParams);
	  virtual void draw();
	  virtual void update();
	  virtual void clean();
private:

};
