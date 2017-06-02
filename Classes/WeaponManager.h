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
	/* 添加需要删除的武器对象 */
	void addDestroyWeapon(Weapons * const &weapon);
private:
	void update(float dt);
	void destroyInvisibleWeapons();	//销毁不可见武器
	Vector<Weapons*> _destroyList;	//销毁列表
};
#endif