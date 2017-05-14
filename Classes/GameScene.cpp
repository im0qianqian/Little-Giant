#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);	
	
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto *sprite = Sprite3D::create("ReskinGirl.c3b");
	sprite->setPosition(Vec2(300, 100));
	sprite->setScale(10.f);
	auto ani = Animation3D::create("orc.c3b");
	auto mat = Animate3D::create(ani);
	sprite->runAction(RepeatForever::create(mat));
	this->addChild(sprite);
	return true;
}