#include "WeaponManager.h"

WeaponManager::WeaponManager():
	_cachePool(ObjCachePool<Weapons>(this, WEAPONS_CACHE_SIZE))
{
	cout << "WeaponManager 构造" << endl;
}

WeaponManager::~WeaponManager()
{
	cout << "WeaponManager 析构" << endl;
}

bool WeaponManager::init()
{
	// 创建缓存池
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
