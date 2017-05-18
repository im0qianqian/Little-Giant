#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class StageManager :public Layer
{
public:
	StageManager();
	~StageManager();
	CREATE_FUNC(StageManager);
	virtual bool init();
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void shootBox(const Vec3 &des);
private:
	bool _needShootBox;
	Camera * _camera;
};

#endif