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
	/* 从缓存池中获取一个奖励对象 */
	Award *getAwardFromPool();
	/* 添加一个奖励对象到缓存池 */
	void addAwardToPool(Award * const &award) { _awardCachePool.pushBack(award); }
	/* 创建所有的奖励对象 */
	void createAllAward();
private:
	const int _cachePoolSize = AWARD_CACHE_SIZE;		// 缓存池容量（场上同时存在的奖励数目）
	void createCachePool();								// 创建缓存池
	Vector<Award*> _awardCachePool;						// 奖励对象缓冲池
};
#endif