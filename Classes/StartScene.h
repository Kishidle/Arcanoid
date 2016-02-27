#pragma once
#include <cocos2d.h>

class StartScene : public cocos2d::Layer {
public:
	static  cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(StartScene);

private:
	cocos2d::Sprite* startButton;
	cocos2d::Sprite* exitButton;
	cocos2d::Sprite* bgImage;
	cocos2d::Sprite* highlight;
	char curSelect;
};