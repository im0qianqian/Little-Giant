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
	bool init();
	/* 创建场景灯光 */
	void createLight();
	/* 创建障碍物 */
	void createObstacles();
	/* 创建地面 */
	void createGround();
	/* GET */
	DirectionLight* getSun()const { return _sun; }
	PointLight* getCharacterLight() const { return _characterLight; }
private:
	void update(float dt);
	Stage *_ground;						//地面
	DirectionLight *_sun;				//太阳
	PointLight *_characterLight;		//人物小灯
};

#endif