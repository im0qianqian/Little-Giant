#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager()
{
}

bool WeaponManager::init()
{
	// ���������
	createCachePool();
	//schedule(schedule_selector(WeaponManager::update), 1.f);
	return true;
}

void WeaponManager::createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos)
{
	/*Weapons *weapon = nullptr;
	switch (weaponType)
	{
	case kWeaponArrow:
		weapon = Arrow::create(owner,spos, epos);
		break;
	case kWeaponBomb:
		weapon = Bomb::create(owner, spos, epos);
		break;
	case kWeaponDart:
		weapon = Dart::create(owner, spos, epos);
		break;
	default:
		break;
	}
	if (weapon != NULL)
	{
		addChild(weapon);
	}*/
	Weapons *weapon = getWeaponFromPool();
	cout << weapon << endl;
	if (weapon != NULL)
	{
		CCASSERT(weapon, "NULL");
		weapon->init(owner, spos, epos);
	}
}

Weapons * WeaponManager::getWeaponFromPool()
{
	Weapons* weapon = nullptr;
	if (!_weaponsCachePool.empty())
	{
		weapon = _weaponsCachePool.back();
		_weaponsCachePool.popBack();
	}
	cout << "�ɹ��ӻ�����л�ȡһ����������" << weapon << endl;
	cout << "��������ش�Сʣ�ࣺ" << _weaponsCachePool.size() << endl;
	return weapon;
}

void WeaponManager::createCachePool()
{
	// ��������
	_weaponsCachePool.clear();
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		Weapons* p = Weapons::create();
		_weaponsCachePool.pushBack(p);
		addChild(p);	//��ӵ�ͼ��
	}
	cout << "��������ش�Сʣ�ࣺ" << _weaponsCachePool.size() << endl;
}
