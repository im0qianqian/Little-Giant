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
	// 每隔10s补充一下场上的奖励数目
	schedule(schedule_selector(AwardManager::update), 10.f);
	return true;
}

void AwardManager::createAllAward()
{
	int size = _cachePool.getResidualSize();
	for (auto i = 0; i < size; i++)
	{
		auto award = _cachePool.getFromPool();			//从缓存池中取出奖励
		if (award != NULL)
		{
			award->initialization();					//登场
		}
	}
	cout << "----------> 成功刷新场上的奖励~~~~~~~~~~~~~~~~" << size<<" "<< _cachePool.getResidualSize()<< endl;
}

void AwardManager::update(float dt)
{
	//创建奖励
	createAllAward();
}
