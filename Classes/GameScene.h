#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
//实现控制各个游戏状态

enum GameStateType	// 游戏状态
{
	kGameStateRuning,	//游戏进行
	kGameStatePause,	//游戏暂停
	kGameStateWin,		//游戏胜利
	kGameStateFail		//游戏失败
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	/* 获取当前游戏状态 */
	static GameStateType getGameState() { return _gameState; }

private:
	static GameStateType _gameState;	// 游戏状态
};
#endif