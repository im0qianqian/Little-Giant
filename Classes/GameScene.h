#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

enum GameState	// сно╥в╢л╛
{
	GameState_Runing,
	GameState_Pause,
	GameState_Win,
	GameState_Fail,
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
	static GameState _gameState;	// сно╥в╢л╛
};
#endif