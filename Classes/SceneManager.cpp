#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::getInstance()
{

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
		break;
	default:
		break;
	}
}