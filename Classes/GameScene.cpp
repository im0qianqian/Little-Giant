#include "GameScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
	bool flag = false;
	if (true)
	{
		_gameState = kGameStateRuning;
		_stage = Stage::create();
		addChild(_stage, 0);
		flag = true;
	}
	return flag;
	//auto *sprite = Sprite3D::create("ReskinGirl.c3b");
	//sprite->setPosition3D(Vec3(300, 100,100));
	//sprite->setScale(10.f);
	//auto ani = Animation3D::create("orc.c3b");
	//auto mat = Animate3D::create(ani);
	//sprite->runAction(RepeatForever::create(mat));
	//this->addChild(sprite);
	//return true;
}

void GameScene::onEnterTransitionDidFinish()
{

}