#include "WeaponManager.h"
#include "Global.h"

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
	auto weapon = _cachePool.getFromPool();
	cout << weapon << endl;
	if (weapon != NULL)
	{
		CCASSERT(weapon, "NULL");
		weapon->init(owner, spos, epos);
	}
}
