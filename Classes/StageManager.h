#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

#include "cocos2d.h"
#include "Stage.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class StageManager :public Layer
{
public:
	StageManager();
	~StageManager();
	CREATE_FUNC(StageManager);
	virtual bool init();
	/* ���������ƹ� */
	void createLight();
	/* �����ϰ��� */
	void createObstacles();
	/* �������� */
	void createGround();
	/* ��ȡ��ǰ�Ƿ���˹��� */
	bool getIsTurnOnLight() const { return _isTurnOnLight; }
	/* ���ù������� */
	void setIsTurnOnLight(const bool &light) { _isTurnOnLight = light; }
	/* GET */
	DirectionLight* getSun()const { return _sun; }
	PointLight* getCharacterLight() const { return _characterLight; }
private:
	void update(float dt);
	Stage *_ground;						//����
	DirectionLight *_sun;				//̫��
	PointLight *_characterLight;		//����С��
	bool _isTurnOnLight;				//�Ƿ���˹���
};

#endif