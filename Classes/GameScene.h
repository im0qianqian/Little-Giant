#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
//实现控制各个游戏状态

enum GameState	// 游戏状态
{
	GameState_Runing,
	GameState_Pause,
	GameState_Win,
	GameState_Fail
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	static cocos2d::Scene* createScene();
private:
	static GameState _gameState;	// 游戏状态
};
#endif