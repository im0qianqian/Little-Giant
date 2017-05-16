#include "SceneManager.h"
#include "GameScene.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

static SceneManager* s_sceneManager = nullptr;		//场景管理者对象
SceneManager* SceneManager::getInstance()
{
	if (!s_sceneManager)
	{
		s_sceneManager = new SceneManager();
		CCASSERT(s_sceneManager, "FATAL: Not enough memory");
	}
	return s_sceneManager;
	return nullptr;
}

void SceneManager::changeScene(SceneType sceneType)
{
	auto scene = Scene::create();
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
	//scene->addChild(_layer);
	Director::getInstance()->runWithScene(scene);
	/*if (Director::getInstance()->getRunningScene())		//如果当前导演正在显示某个场景
	{
		Director::getInstance()->replaceScene(scene);	//替换为当前场景
	}
	else
	{
		Director::getInstance()->runWithScene(scene);	//否则直接显示当前场景
	}*/
}