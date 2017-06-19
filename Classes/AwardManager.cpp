#include "AwardManager.h"
#include "Global.h"

AwardManager::AwardManager():
	_cachePool(ObjCachePool<Award>(this,AWARD_CACHE_SIZE)),
	_allAward(std::set<Award*>())
{
	cout << "AwardManager ����" << endl;
}

AwardManager::~AwardManager()
{
	cout << "AwardManager ����" << endl;
}

bool AwardManager::init()
{
	// ��һ���ȴ��������
	_cachePool.createCachePool();
	// ÿ��10s����һ�³��ϵĽ�����Ŀ
	schedule(schedule_selector(AwardManager::update), 10.f);
	return true;
}

void AwardManager::addToPool(Award * const & award)
{
	_cachePool.addToPool(award);
	_allAward.erase(award);
}

void AwardManager::createAllAward()
{
	int size = _cachePool.getResidualSize();
	for (auto i = 0; i < size; i++)
	{
		auto award = _cachePool.getFromPool();			//�ӻ������ȡ������
		if (award != NULL)
		{
			award->initialization();					//�ǳ�
			_allAward.insert(award);					//���뵽���н�����
		}
	}
	//cout << "----------> �ɹ�ˢ�³��ϵĽ���~~~~~~~~~~~~~~~~" << size<<" "<< _cachePool.getResidualSize()<< endl;
}

void AwardManager::update(float dt)
{
	//��������
	createAllAward();
}
