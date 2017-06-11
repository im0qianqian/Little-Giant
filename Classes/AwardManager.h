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
	virtual bool init() override;
	CREATE_FUNC(AwardManager);
	/* ��Ӷ��󵽻���� */
	void addToPool(Award *const &award) { _cachePool.addToPool(award); }
	/* �������еĽ������� */
	void createAllAward();
private:
	virtual void update(float dt) override;
	ObjCachePool<Award> _cachePool;						//�����
};
#endif