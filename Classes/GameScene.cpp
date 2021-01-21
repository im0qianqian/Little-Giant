#include "GameScene.h"
#include "Global.h"

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
DisplayManager *GameScene::_displayManager = nullptr;
GameModeType GameScene::_gameMode = kGameModeTimer;
unsigned int GameScene::_startingTime = 0;

GameScene::GameScene()
{
	cout << "GameScene 构造" << endl;
}

GameScene::~GameScene()
{
	cout << "GameScene 析构" << endl;
}

bool GameScene::init()
{
	bool flag = false;
	do
	{
		/* 初始化时间种子 */
		srand((unsigned)time(NULL));
		/* 游戏状态 */
		GameScene::_gameState = kGameStateRuning;

		auto _layer3D = Layer::create();	//新建一个图层用来显示3D部分
		/* 摄像机 */
		GameScene::_camera = Camera::createPerspective(60, (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);
		_camera->setCameraFlag(CameraFlag::USER1);
		_layer3D->addChild(_camera);		//将3D摄像机添加进图层

		/* 记录游戏开始的时间 */
		GameScene::_startingTime = unsigned int(GetTickCount64());
		/* 操作管理 */
		GameScene::_joystick = Joystick::create();
		addChild(GameScene::_joystick, -1);
		/* 武器管理 */
		GameScene::_weaponManager = WeaponManager::create();
		_layer3D->addChild(GameScene::_weaponManager, 2);
		/* 人物管理 */
		GameScene::_characterManager = CharacterManager::create();
		_layer3D->addChild(GameScene::_characterManager, 1);
		/* 地图管理 */
		GameScene::_stageManager = StageManager::create();
		_layer3D->addChild(GameScene::_stageManager, 0);
		/* 奖励管理*/
		GameScene::_awardManager = AwardManager::create();
		_layer3D->addChild(GameScene::_awardManager, 3);

		addChild(_layer3D,0);
		
		setCameraMask((unsigned int)CameraFlag::USER1);	//设置当前场景只能被USER1中拍到，以上有效，以下仍然默认
		
		/* 界面显示*/
		GameScene::_displayManager = DisplayManager::create();
		addChild(GameScene::_displayManager, 1);

		//GameScene::_audioManager = AudioManager::create();
		flag = true;
	} while (false);
	return flag;
}

