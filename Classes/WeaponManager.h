#ifndef __WEAPON_MANAGER_H__
#define __WEAPON_MANAGER_H__

#include "cocos2d.h"
#include "Global.h"
#include "ObjCachePool.h"
#include "Weapons.h"

USING_NS_CC;

class WeaponManager :public Layer
{
public:
	WeaponManager();
	~WeaponManager();
	CREATE_FUNC(WeaponManager);
	virtual bool init();
	/* �����������й��� */
	void createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos);
	/* ���һ���������󵽻���� */
	void addToPool(Weapons * const &weapon) { _cachePool.addToPool(weapon); }
private:
	ObjCachePool<Weapons> _cachePool;
};
#endif