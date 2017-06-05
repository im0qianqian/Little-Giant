#include "WeaponManager.h"
#include "Global.h"

WeaponManager::WeaponManager()
{
	_weaponsCachePool.clear();
}

WeaponManager::~WeaponManager()
{
}

bool WeaponManager::init()
{
	// ´´½¨»º´æ³Ø
	_cachePool.setCacheSize(WEAPONS_CACHE_SIZE);
	_cachePool.createCachePool();
	//createCachePool();
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

Weapons * WeaponManager::getWeaponFromPool()
{
	Weapons* weapon = nullptr;
	if (!_weaponsCachePool.empty())
	{
		weapon = _weaponsCachePool.back();
		_weaponsCachePool.popBack();
	}
	cout << "³É¹¦´Ó»º´æ³ØÖÐ»ñÈ¡Ò»¸öÎäÆ÷¶ÔÏó£º" << weapon << endl;
	cout << "ÎäÆ÷»º´æ³Ø´óÐ¡Ê£Óà£º" << _weaponsCachePool.size() << endl;
	return weapon;
}

void WeaponManager::createCachePool()
{
	// »º´æ³ØÇå¿Õ
	_weaponsCachePool.clear();
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		Weapons* p = Weapons::create();
		_weaponsCachePool.pushBack(p);
		addChild(p);	//Ìí¼Óµ½Í¼²ã
	}
	cout << "ÎäÆ÷»º´æ³Ø´óÐ¡Ê£Óà£º" << _weaponsCachePool.size() << endl;
}
