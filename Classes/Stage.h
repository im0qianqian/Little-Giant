#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"

USING_NS_CC;

class Stage :public Sprite3D
{
public:
	Stage();
	~Stage();
	virtual bool init();
	CREATE_FUNC(Stage);
};
#endif