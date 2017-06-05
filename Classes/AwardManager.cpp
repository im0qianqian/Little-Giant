#include "AwardManager.h"

AwardManager::AwardManager()
{
	_awardCachePool.clear();
}

AwardManager::~AwardManager()
{

}

bool AwardManager::init()
{
	// 第一步先创建缓存池
	createCachePool();
	// 第二步创建奖励
	createAllAward();
	return true;
}

Award * AwardManager::getAwardFromPool()
{
	Award* award = nullptr;
	if (!_awardCachePool.empty())
	{
		award = _awardCachePool.back();
		_awardCachePool.popBack();
	}
	cout << "奖励缓存池大小剩余：" << _awardCachePool.size() << endl;
	return award;
}

void AwardManager::createAllAward()
{
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		auto award = getAwardFromPool();	//从缓存池中取出奖励
		if (award != NULL)
		{
			award->initialization();					//登场
		}
	}
}

void AwardManager::createCachePool()
{
	// 缓存池清空
	_awardCachePool.clear();
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		Award* award = Award::create();
		_awardCachePool.pushBack(award);
		addChild(award);	//添加到图层
	}
	cout << "奖励缓存池大小剩余：" << _awardCachePool.size() << endl;
}
