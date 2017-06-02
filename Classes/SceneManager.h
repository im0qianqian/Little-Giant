//ʵ�ֳ���֮��Ĺ������л�

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

enum SceneType
{
	kMenuScene,		//�˵�����
	kLoadingScene,	//���س���
	kGameScene		//��Ϸ����
};

class SceneManager:public Ref
{
public:
	SceneManager();
	~SceneManager();
	bool init();
	CREATE_FUNC(SceneManager);
	/* ��ȡ��ǰ���������� */
	static SceneManager* getInstance();
	/* �л����� */
	void changeScene(const SceneType &sceneType);
	/* ��ȡ��ǰ���� */
	static Scene* getScene() { return _scene; }
	/* ��ȡ��ǰͼ�� */
	static Layer* getLayer() { return _layer; }
private:
	static Scene* _scene;						//��ǰ����
	static Layer* _layer;						//��ǰ����ͼ��
	static SceneManager* s_sceneManager;		//���������߶���
};

#endif