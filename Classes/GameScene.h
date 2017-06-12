#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CharacterManager.h"
#include "WeaponManager.h"
#include "StageManager.h"
#include "AwardManager.h"
#include "AudioManager.h"
#include "DisplayManager.h"
#include "Joystick.h"

USING_NS_CC;
//ʵ�ֿ��Ƹ�����Ϸ״̬

enum GameStateType	// ��Ϸ״̬
{
	kGameStateRuning,	//��Ϸ����
	kGameStatePause,	//��Ϸ��ͣ
	kGameStateWin,		//��Ϸʤ��
	kGameStateFail		//��Ϸʧ��
};

enum GameModeType	// ��Ϸģʽ
{
	kGameModeAdventure,		// ð��ģʽ������������
	kGameModeTimer,			// ��ʱģʽ��ʱ�䵽������
	kGameModeNight			// ��ҹģʽ������������
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init() override;
	/* ��ȡ��ǰ��Ϸ״̬ */
	static GameStateType getGameState() { return _gameState; }
	/* ���ĵ�ǰ��Ϸ״̬ */
	static void setGameState(const GameStateType &gameState) { _gameState = gameState; }
	/* ��ȡ��ǰ��Ϸģʽ */
	static GameModeType getGameMode() { return _gameMode; }
	/* ���ĵ�ǰ��Ϸģʽ */
	static void setGameMode(const GameModeType &gameMode) { _gameMode = gameMode; }
	/* ��ȡ���������� */
	static CharacterManager* getCharacterManager() { return _characterManager; }
	/* ��ȡ��ͼ������� */
	static StageManager* getStageManager() { return _stageManager; }
	/* ��ȡ����������� */
	static WeaponManager* getWeaponManager() { return _weaponManager; }
	/* ��ȡ����������� */
	static AwardManager *getAwardManager() { return _awardManager; }
	/* ��ȡ����������� */
	static AudioManager *getAudioManager() { return _audioManager; }
	/* ��ȡ���������� */
	static DisplayManager *getDisplayManager() { return _displayManager; }
	/* ��ȡ����������� */
	static Joystick *getJoystick() { return _joystick; }
	/* ��ȡ��ǰ����� */
	static Camera *getCamera() { return _camera; }
	/* ��ȡ��Ϸ��ʼʱ�� */
	static int getStartingTime() { return _startingTime; }
private:
	static Camera *_camera;						//��Ϸ�����(3D)
	static GameStateType _gameState;			//��Ϸ״̬
	static CharacterManager *_characterManager;	//����������
	static StageManager *_stageManager;			//��ͼ�������
	static WeaponManager *_weaponManager;		//�����������
	static AwardManager *_awardManager;			//�����������
	static AudioManager *_audioManager;			//�����������
	static DisplayManager *_displayManager;		//������ʾ�������
	static Joystick *_joystick;					//�����������
	static GameModeType _gameMode;				//��Ϸģʽ
	static int _startingTime;					//��Ϸ��ʼʱ��
};

#endif