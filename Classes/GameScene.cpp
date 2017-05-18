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
		/* 场景摄像机创建 */
		GameScene::_camera = Camera::createPerspective(60, (GLfloat)SCREEN_HEIGHT / SCREEN_WIDTH, 1, 1000);
		addChild(_camera);
		addChild(GameScene::_stageManager, 0);
		addChild(GameScene::_characterManager, 1);
		addChild(GameScene::_weaponManager, 1);
		flag = true;
	} while (false);
	return flag;
}

void GameScene::onEnterTransitionDidFinish()
{

}