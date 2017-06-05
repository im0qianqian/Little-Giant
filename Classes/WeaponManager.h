#ifndef __WEAPON_MANAGER_H__
#define __WEAPON_MANAGER_H__

#include "cocos2d.h"
#include "Weapons.h"
#include "Global.h"
#include "ObjCachePool.h"

USING_NS_CC;

class WeaponManager :public Layer
{
public:
	WeaponManager();
	~WeaponManager();
	CREATE_FUNC(WeaponManager);
	virtual bool init();
	/* 创建武器进行攻击 */
	void createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos);
	/* 添加一个武器对象到缓存池 */
	void addToPool(Weapons * const &weapon) { _cachePool.addToPool(weapon); }
private:
	ObjCachePool<Weapons> _cachePool;
};
#endif