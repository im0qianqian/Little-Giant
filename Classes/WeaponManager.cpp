#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager()
{
}

bool WeaponManager::init()
{
	schedule(schedule_selector(WeaponManager::update), 1.f);
	return true;
}

void WeaponManager::createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos)
{
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
	if (weapon != NULL)
	{
		addChild(weapon);
	}
}

void WeaponManager::addDestroyWeapon(Weapons *weapon)
{
	_destroyList.pushBack(weapon);
}

void WeaponManager::update(float dt)
{
	/* 每次 update 销毁一次不可见的武器 */
	destroyInvisibleWeapons();
}

void WeaponManager::destroyInvisibleWeapons()
{
	cout << "-----------------> _destroyList count " << _destroyList.size() << endl;
	while (!_destroyList.empty())
	{
		auto *w = _destroyList.back();
		CCASSERT(w, "NULL");
		w->removeFromParent();
		_destroyList.popBack();
	}
}
