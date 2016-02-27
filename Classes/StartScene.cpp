#include "StartScene.h"
#include "GameScene.h"

USING_NS_CC;
Scene* StartScene::createScene() {
	
	auto scene = Scene::create();

	auto layer = StartScene::create();
	
	scene->addChild(layer);
	
	return scene;
}

bool StartScene::init() {

	curSelect = 's';

	bgImage = Sprite::create("arcanoidv2.png");
	bgImage->setAnchorPoint(Vec2(0, 0));

	this->addChild(bgImage);
	
	startButton = Sprite::create("start_game_1.png");
	startButton->setAnchorPoint(Vec2(0, 0));
	startButton->setPosition(180, 130);
	this->addChild(startButton);

	highlight = Sprite::create("highlight.png");
	highlight->setAnchorPoint(Vec2(0, 0));
	highlight->setPosition(180, 130);

	this->addChild(highlight);
	exitButton = Sprite::create("exit_game_1.png");
	exitButton->setAnchorPoint(Vec2(0, 0));
	exitButton->setPosition(180, 100);
	this->addChild(exitButton);

	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			/*
			startButton->setTexture("start_game_selected_1.png"); //this should be my original code but for some reason it creates read access violations later
			exitButton->setTexture("exit_game_1.png");
			curSelect = 's';*/
			highlight->setPosition(180, 130);
			curSelect = 's';
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			/*
			exitButton->setTexture("exit_game_selected_1.png");
			startButton->setTexture("start_game_1.png");
			curSelect = 'e';*/
			highlight->setPosition(180, 100);

			curSelect = 'e';
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
			if (curSelect == 's') {
				Scene* gameScene = GameScene::createScene();
				
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B(0, 0, 0)));
			}
			else if (curSelect == 'e') {
				Director::sharedDirector()->end();
			}
		}
	};
	this->_eventDispatcher->addEventListenerWithFixedPriority(kbListener, 1);
	return true;
}