#ifndef __WEAPON_MANAGER_H__
#define __WEAPON_MANAGER_H__

#include "cocos2d.h"
#include "Weapons.h"

USING_NS_CC;

class WeaponManager :public Layer
{
public:
	WeaponManager();
	~WeaponManager();
	CREATE_FUNC(WeaponManager);
	virtual bool init();
	/* 创建武器进行攻击 */
	void createWeapon(WeaponType weaponType, void *owner, float power, float speed, float distance, float angle, Vec3 pos);
};
#endif