#ifndef __AWARD_MANAGER_H__
#define __AWARD_MANAGER_H__

#include "cocos2d.h"
#include "Award.h"
#include "Global.h"

USING_NS_CC;

class AwardManager :public Layer
{
public:
	AwardManager();
	~AwardManager();
	virtual bool init();
	CREATE_FUNC(AwardManager);
	/* �ӻ�����л�ȡһ���������� */
	Award *getAwardFromPool();
	/* ���һ���������󵽻���� */
	void addAwardToPool(Award * const &award) { _awardCachePool.pushBack(award); }
	/* �������еĽ������� */
	void createAllAward();
private:
	const int _cachePoolSize = AWARD_CACHE_SIZE;		// ���������������ͬʱ���ڵĽ�����Ŀ��
	void createCachePool();								// ���������
	Vector<Award*> _awardCachePool;						// �������󻺳��
};
#endif