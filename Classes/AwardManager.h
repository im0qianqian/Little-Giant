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
	/* 添加对象到缓存池 */
	void addToPool(Award *const &award) { _cachePool.addToPool(award); }
	/* 创建所有的奖励对象 */
	void createAllAward();
private:
	ObjCachePool<Award> _cachePool;						//缓存池
};
#endif