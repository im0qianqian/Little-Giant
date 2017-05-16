#ifndef __STAGE_MANAGER_H__
#define __STAGE_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class StageManager :public Layer
{
public:
	StageManager();
	~StageManager();
	CREATE_FUNC(StageManager);
	virtual bool init();
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	Camera * _camera;
};

#endif