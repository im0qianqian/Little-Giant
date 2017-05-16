//ʵ�ֳ���֮��Ĺ������л�

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

enum SceneType
{
	kMenuScene,		//�˵�����
	kLoadingScene,	//���س���
	kGameScene		//��Ϸ����
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