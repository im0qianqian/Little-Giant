#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

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

private:
	static GameStateType _gameState;	// ��Ϸ״̬
};
#endif