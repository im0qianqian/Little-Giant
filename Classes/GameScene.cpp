#include "GameScene.h"

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
		/* ��ʼ��ʱ������ */
		srand((unsigned)time(NULL));
		/* ��Ϸ״̬ */
		GameScene::_gameState = kGameStateRuning;
		/* ����� */
		GameScene::_camera = Camera::createPerspective(60, (GLfloat)SCREEN_WIDTH / SCREEN_HEIGHT, 1, 1000);
		_camera->setCameraFlag(CameraFlag::USER1);
		addChild(_camera);
		/* ��ͼ���� */
		GameScene::_stageManager = StageManager::create();
		addChild(GameScene::_stageManager, 0);
		/* ������� */
		GameScene::_characterManager = CharacterManager::create();
		addChild(GameScene::_characterManager, 1);
		/* �������� */
		GameScene::_weaponManager = WeaponManager::create();
		addChild(GameScene::_weaponManager, 2);
		/* ��������*/
		GameScene::_awardManager = AwardManager::create();
		addChild(GameScene::_awardManager, 3);
		/* �������� */
		GameScene::_joystick = Joystick::create();
		addChild(GameScene::_joystick, -1);

		//GameScene::_audioManager = AudioManager::create();

		/* ���õ�ǰ������ USER1 �пɼ�������Ҫ���������ͼ�� addChild ֮�� */
		setCameraMask((unsigned int)CameraFlag::USER1);

		flag = true;
	} while (false);
	return flag;
}
