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
	virtual bool init() override;
	/* ���������ƹ� */
	void createLight();
	/* �����ϰ��� */
	void createObstacles();
	/* �������� */
	void createGround();
	/* GET */
	DirectionLight* getSun()const { return _sun; }
	PointLight* getCharacterLight() const { return _characterLight; }
	/* ��ȡ��ǰ��ͼ */
	void getCMap(int map[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH]);
	auto getMap() const { return _map; }
	Stage *getGround() { return _ground; }
private:
	void updateMap(float dt);
	virtual void update(float dt) override;
	Stage *_ground;									//����
	DirectionLight *_sun;							//̫��
	PointLight *_characterLight;					//����С��
	int _map[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH];	//��ǰ��ͼ
	int _cMap[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH];	//��ͼ�е������Լ�����
};

#endif