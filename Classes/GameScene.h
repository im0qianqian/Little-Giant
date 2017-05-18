#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CharacterManager.h"
#include "WeaponManager.h"
#include "StageManager.h"
#include "AwardManager.h"
#include "AudioManager.h"

USING_NS_CC;
//ʵ�ֿ��Ƹ�����Ϸ״̬

enum GameStateType	// ��Ϸ״̬
{
	kGameStateRuning,	//��Ϸ����
	kGameStatePause,	//��Ϸ��ͣ
	kGameStateWin,		//��Ϸʤ��
	kGameStateFail		//��Ϸʧ��
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	/* ��ȡ��ǰ��Ϸ״̬ */
	static GameStateType getGameState() { return _gameState; }
	/* ��ȡ���������� */
	static CharacterManager* getCharacterManager() { return _characterManager; }
	/* ��ȡ��ͼ������� */
	static StageManager* getStage() { return _stageManager; }
	/* ��ȡ����������� */
	static WeaponManager* getWeaponManager() { return _weaponManager; }
private:
	static Camera *_camera;						//���������
	static GameStateType _gameState;			//��Ϸ״̬
	static CharacterManager *_characterManager;	//����������
	static StageManager *_stageManager;			//��ͼ�������
	static WeaponManager *_weaponManager;		//�����������
	static AwardManager *_awardManager;			//�����������
	static AudioManager *_audioManager;			//�����������
};


#endif