#ifndef __AWARD_MANAGER_H__
#define __AWARD_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class AwardManager :public Layer
{
public:
	AwardManager();
	~AwardManager();
	virtual bool init();
	CREATE_FUNC(AwardManager);
};
#endif