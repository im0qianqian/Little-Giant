#ifndef __AWARD_MANAGER_H__
#define __AWARD_MANAGER_H__

#include "cocos2d.h"
#include "Award.h"
#include "ObjCachePool.h"

USING_NS_CC;

class AwardManager :public Layer
{
public:
	AwardManager();
	~AwardManager();
	virtual bool init();
	CREATE_FUNC(AwardManager);
	/* ��Ӷ��󵽻���� */
	void addToPool(Award *const &award) { _cachePool.addToPool(award); }
	/* �������еĽ������� */
	void createAllAward();
private:
	ObjCachePool<Award> _cachePool;						//�����
};
#endif