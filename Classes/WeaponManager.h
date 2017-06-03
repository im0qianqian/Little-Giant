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
	/* �����������й��� */
	void createWeapon(WeaponType weaponType, void *owner, Vec3 spos, Vec3 epos);
	/* �ӻ�����л�ȡһ���������� */
	Weapons *getWeaponFromPool();
	/* ���һ���������󵽻���� */
	void addWeaponToPool(Weapons * const &weapon) { _weaponsCachePool.pushBack(weapon); }
private:
	const int _cachePoolSize = 100;		// ���������������ͬʱ�����������Ŀ��
	void createCachePool();				// ���������
	Vector<Weapons*> _weaponsCachePool;	// �������󻺳��
};
#endif