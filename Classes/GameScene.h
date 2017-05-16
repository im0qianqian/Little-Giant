#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CharacterManager.h"
#include "WeaponManager.h"
#include "Stage.h"

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
	static Stage* getStage() { return _stage; }
	/* ��ȡ����������� */
	static WeaponManager* getWeaponManager() { return _weaponManager; }
private:
	static GameStateType _gameState;			//��Ϸ״̬
	static CharacterManager *_characterManager;	//����������
	static Stage *_stage;						//��ͼ�������
	static WeaponManager *_weaponManager;		//�����������
};
#endif