//实现场景之间的管理与切换

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

enum SceneType
{
	kMenuScene,		//菜单场景
	kLoadingScene,	//加载场景
	kGameScene		//游戏场景
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	static SceneManager* getInstance();
	void changeScene(SceneType sceneType);
private:
	static SceneManager* _sceneManager;
};
#endif