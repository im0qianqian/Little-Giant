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
	virtual bool init();
	CREATE_FUNC(SceneManager);
	/* ��ȡ��ǰ���������� */
	static SceneManager* getInstance();
	/* �л����� */
	void changeScene(SceneType sceneType);
private:
	Camera *_camera;							//��ǰ���������
	Layer* _layer;								//��ǰ����ͼ��
	static SceneManager* s_sceneManager;		//���������߶���
};

#endif