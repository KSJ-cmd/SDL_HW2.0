#pragma once

#include"SDLGameObject.h"

class Map : public SDLGameObject
{
public:
	Map(const LoaderParams* pParams);
	~Map();
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}
private:
	int maps[19] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

};


