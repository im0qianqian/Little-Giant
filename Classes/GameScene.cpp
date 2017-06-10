#include "GameScene.h"
#include "Global.h"

USING_NS_CC;

/* �ྲ̬˽�б�����ʼ�� */
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

GameScene::GameScene()
{

} 

GameScene::~GameScene()
{
	GameScene::_camera = nullptr;
	GameScene::_gameState = kGameStatePause;
	GameScene::_characterManager = nullptr;
	GameScene::_stageManager = nullptr;
	GameScene::_weaponManager = nullptr;
	GameScene::_awardManager = nullptr;
	GameScene::_audioManager = nullptr;
	GameScene::_joystick = nullptr;
	GameScene::_displayManager = nullptr;
	GameScene::_gameMode = kGameModeTimer;
}

bool GameScene::init()
{
	bool flag = false;
	do
	{
		/* ��ʼ��ʱ������ */
		srand((unsigned)time(NULL));
		/* ��Ϸ״̬ */
		GameScene::_gameState = kGameStateRuning;

		auto _layer3D = Layer::create();	//�½�һ��ͼ��������ʾ3D����
		/* ����� */
		GameScene::_camera = Camera::createPerspective(60, (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);
		_camera->setCameraFlag(CameraFlag::USER1);
		_layer3D->addChild(_camera);		//��3D�������ӽ�ͼ��
		/* �������� */
		GameScene::_joystick = Joystick::create();
		addChild(GameScene::_joystick, -1);
		/* ������� */
		GameScene::_characterManager = CharacterManager::create();
		_layer3D->addChild(GameScene::_characterManager, 1);
		/* ��ͼ���� */
		GameScene::_stageManager = StageManager::create();
		_layer3D->addChild(GameScene::_stageManager, 0);
		/* �������� */
		GameScene::_weaponManager = WeaponManager::create();
		_layer3D->addChild(GameScene::_weaponManager, 2);
		/* ��������*/
		GameScene::_awardManager = AwardManager::create();
		_layer3D->addChild(GameScene::_awardManager, 3);

		addChild(_layer3D);
		
		setCameraMask((unsigned int)CameraFlag::USER1);	//���õ�ǰ����ֻ�ܱ�USER1���ĵ���������Ч��������ȻĬ��
		
		/* ������ʾ*/
		GameScene::_displayManager = DisplayManager::create();
		addChild(GameScene::_displayManager, 4);

		//GameScene::_audioManager = AudioManager::create();
		flag = true;
	} while (false);
	return flag;
}
