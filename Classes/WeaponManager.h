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
	void update(float dt);
	void destroyInvisibleWeapons();	//���ٲ��ɼ�����
	Vector<Weapons*> _destroyList;	//�����б�
};
#endif