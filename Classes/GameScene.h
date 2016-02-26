#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <map>
#include <vector>
class GameScene : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void update(float) override;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	void playerMovement(cocos2d::EventKeyboard::KeyCode);

	CREATE_FUNC(GameScene);
private:
	char curDir;

	cocos2d::Sprite* paddle;
	cocos2d::Sprite* ball;
	cocos2d::Sprite* block;
	cocos2d::Vec2 paddlePos;
	cocos2d::Vec2 ballPos;
	cocos2d::PhysicsBody* paddleBody;
	cocos2d::PhysicsBody* ballBody;
	cocos2d::PhysicsBody* blockBody;
	cocos2d::PhysicsBody* edgeBody;
	
	bool gameStart;
	static std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> keys;
	
	cocos2d::PhysicsWorld *gameWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { gameWorld = world; };
	
	bool onContactBegin(cocos2d::PhysicsContact &contact);

public: 
	
};
