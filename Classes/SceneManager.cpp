#include "SceneManager.h"
#include "GameScene.h"

/* 类静态私有变量初始化 */
SceneManager* SceneManager::s_sceneManager = nullptr;

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

void SceneManager::changeScene(SceneType sceneType)
{
	auto scene = Scene::createWithPhysics();
	switch (sceneType)
	{
	case kMenuScene:
		break;
	case kLoadingScene:
		break;
	case kGameScene:
		_layer = GameScene::create();
		break;
	default:
		break;
	}
	/* 设置物理世界Debug模式打开*/
	scene->getPhysics3DWorld()->setDebugDrawEnable(true);
	scene->addChild(_layer);
	if (Director::getInstance()->getRunningScene())		//如果当前导演正在显示某个场景
	{
		Director::getInstance()->replaceScene(scene);	//替换为当前场景
	}
	else
	{
		Director::getInstance()->runWithScene(scene);	//否则直接显示当前场景
	}
}