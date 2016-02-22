#include "GameScene.h"
#include "SimpleAudioEngine.h"
//make a datamanager class later
USING_NS_CC;

Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;

}

bool GameScene::init() {
	//code here LOL

	auto paddle = Sprite::create("paddle.png");
	this->addChild(paddle);
	return true;
}

void GameScene::update(float delta) {

}
