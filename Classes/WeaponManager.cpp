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

void WeaponManager::createWeapon(WeaponType weaponType, void * owner, float power, float speed, float distance, float angle, Vec3 pos)
{
	CCLOG("create success!");
	switch (weaponType)
	{
	case kWeaponArrow:
		Arrow::create(owner, power, speed, distance, angle, pos);
		break;
	case kWeaponBomb:
		Bomb::create(owner, power, speed, distance, angle, pos);
		break;
	case kWeaponDart:
		Dart::create(owner, power, speed, distance, angle, pos);
		break;
	default:
		break;
	}
}
