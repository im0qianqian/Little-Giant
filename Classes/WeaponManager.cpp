#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager()
{
}

bool WeaponManager::init()
{
	return true;
}

void WeaponManager::createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos)
{
	CCLOG("create success!");
	switch (weaponType)
	{
	case kWeaponArrow:
		Arrow::create(owner, 1, 100.0f, 1, spos, epos);
		break;
	case kWeaponBomb:
		Bomb::create(owner, 1, 100, 1, spos, epos);
		break;
	case kWeaponDart:
		Dart::create(owner, 1, 100, 1, spos, epos);
		break;
	default:
		break;
	}
}
