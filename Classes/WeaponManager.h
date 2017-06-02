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
	/* �����Ҫɾ������������ */
	void addDestroyWeapon(Weapons * const &weapon);
private:
	const int _cachePoolSize = 300;
	void update(float dt);
	void destroyInvisibleWeapons();		//���ٲ��ɼ�����
	void createCachePool();				// ���������
	Vector<Weapons*> _weaponsCachePool;	// �������󻺳��
	Vector<Weapons*> _destroyList;		// �����б�
};
#endif