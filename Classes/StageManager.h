#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

#include "cocos2d.h"
#include "Stage.h"
#include "Global.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class StageManager :public Layer
{
public:
	StageManager();
	~StageManager();
	CREATE_FUNC(StageManager);
	bool init();
	/* ���������ƹ� */
	void createLight();
	/* �����ϰ��� */
	void createObstacles();
	/* �������� */
	void createGround();
	/* GET */
	DirectionLight* getSun()const { return _sun; }
	PointLight* getCharacterLight() const { return _characterLight; }
private:
	void update(float dt);
	Stage *_ground;									//����
	DirectionLight *_sun;							//̫��
	PointLight *_characterLight;					//����С��
	int _map[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH];	//��ǰ��ͼ
};

#endif