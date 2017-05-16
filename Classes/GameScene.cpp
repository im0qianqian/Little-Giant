#include "GameScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

/* 类静态私有变量初始化 */
GameStateType GameScene::_gameState = kGameStatePause;
CharacterManager *GameScene::_characterManager = nullptr;
StageManager *GameScene::_stageManager = nullptr;
WeaponManager *GameScene::_weaponManager = nullptr;

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
		GameScene::_gameState = kGameStateRuning;
		GameScene::_stageManager = StageManager::create();
		addChild(GameScene::_stageManager, 0);
		flag = true;
	}
	return flag;
}

void GameScene::onEnterTransitionDidFinish()
{

}