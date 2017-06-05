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
	// ��һ���ȴ��������
	createCachePool();
	// �ڶ�����������
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
	cout << "��������ش�Сʣ�ࣺ" << _awardCachePool.size() << endl;
	return award;
}

void AwardManager::createAllAward()
{
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		auto award = getAwardFromPool();	//�ӻ������ȡ������
		if (award != NULL)
		{
			award->initialization();					//�ǳ�
		}
	}
}

void AwardManager::createCachePool()
{
	// ��������
	_awardCachePool.clear();
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		Award* award = Award::create();
		_awardCachePool.pushBack(award);
		addChild(award);	//��ӵ�ͼ��
	}
	cout << "��������ش�Сʣ�ࣺ" << _awardCachePool.size() << endl;
}
