#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene :public Layer
{
public:
	//GameScene();
	//~GameScene();
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
};
#endif