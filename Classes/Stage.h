#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"

USING_NS_CC;

class Stage :public Layer
{
public:
	Stage();
	~Stage();
	CREATE_FUNC(Stage);
	virtual bool init();
};

#endif