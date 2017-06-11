#include "WeaponManager.h"

WeaponManager::WeaponManager():
	_cachePool(ObjCachePool<Weapons>(this, WEAPONS_CACHE_SIZE))
{
}

WeaponManager::~WeaponManager()
{
}

bool WeaponManager::init()
{
	// ´´½¨»º´æ³Ø
	_cachePool.createCachePool();
	//schedule(schedule_selector(WeaponManager::update), 1.f);
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
