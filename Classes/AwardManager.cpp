#include "AwardManager.h"
#include "Global.h"

AwardManager::AwardManager():
	_cachePool(ObjCachePool<Award>(this,AWARD_CACHE_SIZE))
{
}

AwardManager::~AwardManager()
{

}

bool AwardManager::init()
{
	// 第一步先创建缓存池
	_cachePool.createCachePool();
	// 第二步创建奖励
	createAllAward();
	return true;
}

void AwardManager::createAllAward()
{
	for (auto i = 0; i < AWARD_CACHE_SIZE; i++)
	{
		auto award = _cachePool.getFromPool();			//从缓存池中取出奖励
		if (award != NULL)
		{
			award->initialization();					//登场
		}
	}
}
