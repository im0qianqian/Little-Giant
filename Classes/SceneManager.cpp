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
	/* ������������Debugģʽ��*/
	scene->getPhysics3DWorld()->setDebugDrawEnable(true);

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