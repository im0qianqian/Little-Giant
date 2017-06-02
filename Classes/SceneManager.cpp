#include "SceneManager.h"
#include "GameScene.h"
#include "LoadLayer.h"

/* �ྲ̬˽�б�����ʼ�� */
SceneManager* SceneManager::s_sceneManager = nullptr;
Scene* SceneManager::_scene = nullptr;						//��ǰ����
Layer* SceneManager::_layer = nullptr;								//��ǰ����ͼ��

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
	/* ������������Debug��� */
	_scene->setPhysics3DDebugCamera(GameScene::getCamera());
	_scene->addChild(_layer);
	if (Director::getInstance()->getRunningScene())		//�����ǰ����������ʾĳ������
	{
		Director::getInstance()->replaceScene(_scene);	//�滻Ϊ��ǰ����
	}
	else
	{
		Director::getInstance()->runWithScene(_scene);	//����ֱ����ʾ��ǰ����
	}
}