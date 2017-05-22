#include "GameScene.h"
#include "Global.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

/* 类静态私有变量初始化 */
Camera *GameScene::_camera = nullptr;
GameStateType GameScene::_gameState = kGameStatePause;
CharacterManager *GameScene::_characterManager = nullptr;
StageManager *GameScene::_stageManager = nullptr;
WeaponManager *GameScene::_weaponManager = nullptr;
AwardManager *GameScene::_awardManager = nullptr;
AudioManager *GameScene::_audioManager = nullptr;
Joystick *GameScene::_joystick = nullptr;

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
		/* 游戏状态 */
		GameScene::_gameState = kGameStateRuning;
		/* 摄像机 */
		GameScene::_camera = Camera::createPerspective(60, (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);
		_camera->setCameraFlag(CameraFlag::USER1);
		addChild(_camera);
		/* 地图管理 */
		GameScene::_stageManager = StageManager::create();
		addChild(GameScene::_stageManager, 0);
		/* 人物管理 */
		GameScene::_characterManager = CharacterManager::create();
		addChild(GameScene::_characterManager, 1);
		/* 武器管理 */
		GameScene::_weaponManager = WeaponManager::create();
		addChild(GameScene::_weaponManager, 2);
		/* 操作管理 */
		GameScene::_joystick = Joystick::create();
		addChild(GameScene::_joystick, -1);
		//GameScene::_awardManager = AwardManager::create();
		//GameScene::_audioManager = AudioManager::create();
		flag = true;
	} while (false);
	return flag;
}
