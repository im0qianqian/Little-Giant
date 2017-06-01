#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Stage :public PhysicsSprite3D
{
public:
	Stage();
	~Stage();
	virtual bool init();
	static Stage* create(Physics3DRigidBodyDes *rbDes, const std::string &ptr, const std::string &texture);
};
#endif