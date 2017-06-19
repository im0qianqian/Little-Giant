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
	void addToPool(Award *const &award);
	/* ��ȡ���н������� */
	std::set<Award*> &getAllAward() { return _allAward; }
private:
	/* �������еĽ������� */
	void createAllAward();
	virtual void update(float dt) override;
	std::set<Award*> _allAward;							//���н���
	ObjCachePool<Award> _cachePool;						//�����
};
#endif