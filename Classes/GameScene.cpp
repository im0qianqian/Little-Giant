#include "GameScene.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

/* 类静态私有变量初始化 */
GameStateType GameScene::_gameState = kGameStatePause;
CharacterManager *GameScene::_characterManager = nullptr;
StageManager *GameScene::_stageManager = nullptr;
WeaponManager *GameScene::_weaponManager = nullptr;
AwardManager *GameScene::_awardManager = nullptr;
AudioManager *GameScene::_audioManager = nullptr;

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
	bool flag = false;
	do
	{
		GameScene::_gameState = kGameStateRuning;
		GameScene::_characterManager = CharacterManager::create();
		GameScene::_stageManager = StageManager::create();
		GameScene::_weaponManager = WeaponManager::create();
		GameScene::_awardManager = AwardManager::create();
		GameScene::_audioManager = AudioManager::create();
		addChild(GameScene::_stageManager, 0);
		flag = true;
	} while (false);
	return flag;
}

void GameScene::onEnterTransitionDidFinish()
{

}