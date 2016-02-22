#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(GameScene);
	void update(float) override;
};