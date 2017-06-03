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
	void createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos);
	/* 从缓存池中获取一个武器对象 */
	Weapons *getWeaponFromPool();
	/* 添加一个武器对象到缓存池 */
	void addWeaponToPool(Weapons * const &weapon) { _weaponsCachePool.pushBack(weapon); }
private:
	const int _cachePoolSize = 100;		// 缓存池容量（场上同时发射的武器数目）
	void createCachePool();				// 创建缓存池
	Vector<Weapons*> _weaponsCachePool;	// 武器对象缓冲池
};
#endif