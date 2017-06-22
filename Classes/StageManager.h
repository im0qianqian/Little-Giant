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
	/* 创建场景灯光 */
	void createLight();
	/* 创建障碍物 */
	void createObstacles();
	/* 创建地面 */
	void createGround();
	/* GET */
	DirectionLight* getSun()const { return _sun; }
	PointLight* getCharacterLight() const { return _characterLight; }
	/* 获取当前地图 */
	void getCMap(int map[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH]);
	const int(*getMap())[50] { return _map; }
	Stage *getGround() { return _ground; }
private:
	void updateMap(float dt);
	virtual void update(float dt) override;
	Stage *_ground;									//地面
	DirectionLight *_sun;							//太阳
	PointLight *_characterLight;					//人物小灯
	int _map[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH];	//当前地图
	int _cMap[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH];	//地图中的人物以及奖励
};

#endif