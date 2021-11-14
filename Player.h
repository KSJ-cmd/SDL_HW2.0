#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "SDLGameObject.h"
#include <iostream>
#include <vector>
#include<list>
#include<memory>

class MouseState;

class Player : public SDLGameObject {
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void handleInput();
	void setState(std::shared_ptr<MouseState> MouseState);
	void Click();

	void Gravity();

	void CreateBullet();

private:
	std::shared_ptr<MouseState> m_pMouseState = nullptr;

	std::list<GameObject*> m_bullets;

	bool isClick = false;
	bool isJump = false;
};



class MouseState {
public:
	virtual void Click(Player* ButtonState) {}
};

class ButtonDown :public MouseState {
public:
	static std::shared_ptr<ButtonDown>& Instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = std::make_shared<ButtonDown>();
		}
		return s_pInstance;
	}
	virtual void Click(Player* ButtonState);
private:
	//ButtonDown() {}
	static std::shared_ptr<ButtonDown> s_pInstance;
};

class ButtonUp : public MouseState {
public:
	static std::shared_ptr<ButtonUp>& Instance() {
		if (s_pInstance == nullptr) {
			s_pInstance = std::make_shared<ButtonUp>();
		}
		return s_pInstance;
	}
	virtual void Click(Player* ButtonState);
private:
	//ButtonUp() {}
	static std::shared_ptr<ButtonUp> s_pInstance;
};

#endif