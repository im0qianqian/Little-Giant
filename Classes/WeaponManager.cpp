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
	Weapons *weapon = nullptr;
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
	addChild(weapon);
}
