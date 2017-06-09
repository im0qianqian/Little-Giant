#include "SceneManager.h"
#include "GameScene.h"
#include "Global.h"
#include "LoadLayer.h"

/* 类静态私有变量初始化 */
SceneManager* SceneManager::s_sceneManager = nullptr;
Scene* SceneManager::_scene = nullptr;						//当前场景
Layer* SceneManager::_layer = nullptr;								//当前场景图层

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::init()
{
	return true;
}

SceneManager* SceneManager::getInstance()
{
	if (!s_sceneManager)
	{
		s_sceneManager = SceneManager::create();
		CCASSERT(s_sceneManager, "FATAL: Not enough memory");
	}
	return s_sceneManager;
}

void SceneManager::changeScene(const SceneType &sceneType)
{
	_scene = Scene::createWithPhysics();
	switch (sceneType)
	{
	case kMenuScene:
		break;
	case kLoadingScene:
		_layer = LoadLayer::create();
		break;
	case kGameScene:
		_layer = GameScene::create();
		break;
	default:
		break;
	}
	/* 设置物理世界Debug相机 */
	_scene->setPhysics3DDebugCamera(GameScene::getCamera());
	_scene->addChild(_layer);
	if (Director::getInstance()->getRunningScene())		//如果当前导演正在显示某个场景
	{
		Director::getInstance()->replaceScene(_scene);	//替换为当前场景
	}
	else
	{
		Director::getInstance()->runWithScene(_scene);	//否则直接显示当前场景
	}
}