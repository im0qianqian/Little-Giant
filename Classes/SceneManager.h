//实现场景之间的管理与切换

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

enum SceneType
{
	kMenuScene,		//菜单场景
	kLoadingScene,	//加载场景
	kGameScene,		//游戏场景
	kHelpScene      //帮助场景
};

class SceneManager:public Ref
{
public:
	SceneManager();
	~SceneManager();
	bool init();
	CREATE_FUNC(SceneManager);
	/* 获取当前场景管理者 */
	static SceneManager* getInstance();
	/* 切换场景 */
	void changeScene(const SceneType &sceneType);
	/* 获取当前场景 */
	static Scene* getScene() { return _scene; }
	/* 获取当前图层 */
	static Layer* getLayer() { return _layer; }
private:
	static Scene* _scene;						//当前场景
	static Layer* _layer;						//当前场景图层
	static SceneManager* s_sceneManager;		//场景管理者对象
};

#endif