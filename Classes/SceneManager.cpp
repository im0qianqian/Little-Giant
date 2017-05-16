#include "SceneManager.h"
#include "GameScene.h"

/* �ྲ̬˽�б�����ʼ�� */
SceneManager* SceneManager::s_sceneManager = nullptr;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

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
	scene->addChild(_layer);
	if (Director::getInstance()->getRunningScene())		//�����ǰ����������ʾĳ������
	{
		Director::getInstance()->replaceScene(scene);	//�滻Ϊ��ǰ����
	}
	else
	{
		Director::getInstance()->runWithScene(scene);	//����ֱ����ʾ��ǰ����
	}
}