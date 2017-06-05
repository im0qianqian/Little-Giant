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
	// ��һ���ȴ��������
	_cachePool.createCachePool();
	// �ڶ�����������
	createAllAward();
	return true;
}

void AwardManager::createAllAward()
{
	for (auto i = 0; i < AWARD_CACHE_SIZE; i++)
	{
		auto award = _cachePool.getFromPool();			//�ӻ������ȡ������
		if (award != NULL)
		{
			award->initialization();					//�ǳ�
		}
	}
}
