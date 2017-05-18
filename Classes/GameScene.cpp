#include "GameScene.h"
#include "Global.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

/* �ྲ̬˽�б�����ʼ�� */
GameStateType GameScene::_gameState = kGameStatePause;
CharacterManager *GameScene::_characterManager = nullptr;
StageManager *GameScene::_stageManager = nullptr;
WeaponManager *GameScene::_weaponManager = nullptr;
AwardManager *GameScene::_awardManager = nullptr;
AudioManager *GameScene::_audioManager = nullptr;
Camera *GameScene::_camera = nullptr;

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
		GameScene::_camera = Camera::createPerspective(60, (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);
		addChild(_camera);
		GameScene::_characterManager = CharacterManager::create();
		GameScene::_stageManager = StageManager::create();
		//GameScene::_weaponManager = WeaponManager::create();
		//GameScene::_awardManager = AwardManager::create();
		//GameScene::_audioManager = AudioManager::create();
		addChild(GameScene::_stageManager, 0);
		addChild(GameScene::_characterManager, 1);
		
		flag = true;
	} while (false);
	return flag;
}
