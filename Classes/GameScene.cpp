#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "EndScene.h"
//make a datamanager class later
USING_NS_CC;

Scene* GameScene::createScene() {
	auto scene = Scene::createWithPhysics();

	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	
	auto layer = GameScene::create();

	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;

}

bool GameScene::init() {

	int i = 0;
	int n = 0;
	int tag = 0;
	int blockX = 10;
	int blockY = 600;
	lives = 3;
	numBlocks = 60;
	curDir = 'x';
	gameStart = false;

	auto bgImage = Sprite::create("arcanoidv2.png");
	bgImage->setAnchorPoint(Vec2(0.0, 0.0));
	
	this->addChild(bgImage, 0);
	
	livesLabel = Label::createWithSystemFont("Lives: " + std::to_string(lives), "Arial", 18);
	livesLabel->setPosition(0, 0);
	livesLabel->setAnchorPoint(Vec2(0, 0));
	this->addChild(livesLabel);

	scoreLabel = Label::createWithSystemFont("# of blocks remaining: " + std::to_string(numBlocks), "Arial", 18);
	scoreLabel->setPosition(0, 18);
	scoreLabel->setAnchorPoint(Vec2(0, 0));
	this->addChild(scoreLabel);

	paddle = Sprite::create("paddle.png");
	paddle->setPosition(200, 100);
	paddle->setAnchorPoint(Vec2(0, 0));
	paddleBody = PhysicsBody::createBox(paddle->getContentSize(), PhysicsMaterial(0, 10, 0));
	paddleBody->setCollisionBitmask(1);
	paddleBody->setContactTestBitmask(true);
	paddleBody->setDynamic(false);
	paddle->setPhysicsBody(paddleBody);
	this->addChild(paddle);
	
	
	ball = Sprite::create("ball test.png");
	ball->setPosition(230, 123);
	ballBody = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
	ballBody->setCollisionBitmask(2);
	ballBody->setContactTestBitmask(true);
	ballBody->setVelocityLimit(400);
	ball->setPhysicsBody(ballBody);
	paddle->setAnchorPoint(Vec2(0, 0));
	this->addChild(ball);

	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//create physics
	edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height /2 + origin.y));
	edgeNode->setAnchorPoint(Vec2(0, 0));
	edgeBody->setDynamic(false);
	edgeBody->setCollisionBitmask(4);
	edgeBody->setContactTestBitmask(true);
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	for (n = 0; n < 5; n++) {
		for (i = 0; i < 12; i++) {
			block = Sprite::create("normal_block.png");
			block->setPosition(blockX, blockY);
			blockBody = PhysicsBody::createCircle(block->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
			blockBody->setCollisionBitmask(3);
			blockBody->setContactTestBitmask(true);
			blockBody->setTag(tag);
			blockBody->setDynamic(false);
			block->setTag(tag);
			block->setPhysicsBody(blockBody);
			block->setAnchorPoint(Vec2(0, 0));
			this->addChild(block);

			tag++;
			blockX += 42;
		}
		blockY -= 30;
		blockX = 10;
	}
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);

	//creating keyboard listener
	auto kbListener = EventListenerKeyboard::create();
	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	kbListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] == std::chrono::high_resolution_clock::now();
		}
		if (gameStart == false) {
			if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
				ballBody->applyImpulse(Vect(100, 400));
				gameStart = true;
			}
		}
		return true;
	};
	kbListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys.erase(keyCode);
	};


	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(kbListener, paddle);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	this->scheduleUpdate();
	return true;


}
void GameScene::resetState() {
	gameStart = false;
	paddle->setPosition(200, 100);
	ball->setPosition(230, 123);
}
void GameScene::updateScore() {

	numBlocks--;
	scoreLabel->setString("# of blocks remaining: " + std::to_string(numBlocks));

}
bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact) {

	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	Vec2 ballPos = ball->getPosition();

	if (ball->getPositionY() < paddle->getPositionY()) {
		return false;
	}
	if (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 3) {
		removeChildByTag(b->getTag(), true);
		updateScore();
		
	}
	if (a->getCollisionBitmask() == 3 && b->getCollisionBitmask() == 2) {
		removeChildByTag(a->getTag(), true);
		updateScore();
	}
	
	
	return true;
}


bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys.find(keyCode) != keys.end())
		return true;
	return false;
}

void GameScene::playerMovement(EventKeyboard::KeyCode keyCode) {
	paddlePos = paddle->getPosition();
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		curDir = 'a';
			
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		curDir = 'd';
	}
	else curDir = 'n';
	
}


void GameScene::update(float delta) {
	paddlePos = paddle->getPosition();
	ballPos = ball->getPosition();
	Node::update(delta);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		curDir = 'a';
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		curDir = 'd';
	}
	else curDir = 'n';

	if (curDir == 'a') {
		
		paddlePos.x = paddlePos.x - 150 * delta;
		if(!gameStart) ballPos.x = ballPos.x - 150 * delta;
	}
	if (curDir == 'd') {
		paddlePos.x = paddlePos.x + 150 * delta;
		if(!gameStart) ballPos.x = ballPos.x + 150 * delta;
		
	}
	if(!(paddlePos.x < 0 || paddlePos.x > 417))
	paddle->setPosition(paddlePos);
	
	if (!gameStart) {
		ballPos.y = 123;
		ball->setPosition(ballPos);
	}
	if (ballPos.y < this->getBoundingBox().getMinY()) {
		lives--;
		if (lives > 0) {
			resetState();
			ballBody->setVelocity(Vect(0, 0));
			livesLabel->setString("Lives: " + std::to_string(lives));
		}
		else {
			Scene* resetScene = GameScene::createScene();
			Director::getInstance()->replaceScene(resetScene);
		}
	}
	
}
std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> GameScene::keys;