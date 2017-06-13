#include "WeaponManager.h"

WeaponManager::WeaponManager():
	_cachePool(ObjCachePool<Weapons>(this, WEAPONS_CACHE_SIZE))
{
	cout << "WeaponManager ����" << endl;
}

WeaponManager::~WeaponManager()
{
	cout << "WeaponManager ����" << endl;
}

bool WeaponManager::init()
{
	// ���������
	_cachePool.createCachePool();
	return true;
}

void WeaponManager::createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos)
{
	auto weapon = _cachePool.getFromPool();
	if (weapon != NULL)
	{
		CCASSERT(weapon, "NULL");
		weapon->init(owner, spos, epos);
	}
}
