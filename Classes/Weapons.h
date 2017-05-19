//ʵ�ָ������������������

#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Global.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

enum WeaponType
{
	kWeaponArrow,
	kWeaponBomb,
	kWeaponDart
};

class Weapons :public PhysicsSprite3D
{
public:
	Weapons();
	~Weapons();
	/* ��ȡ������������ */
	virtual void* getOwner() { return _owner; }
	/* ��ȡ������ */
	virtual float getPower() { return _power; }
	/* ��ȡ�����ٶ� */
	virtual float getSpeed() { return _speed; }
	/* ��ȡ��ʼ������ */
	virtual Vec3 getSpos() { return _spos; }
	/* ��ȡĿ������� */
	virtual Vec3 getEpos() { return _epos; }
	virtual void attack() = 0;
protected:
	/* ��ʼ������ */
	virtual bool init(void *owner, float power, float speed, float distance, Vec3 spos, Vec3 epos);
private:
	void *_owner;			//������������
	float _power;			//������
	float _speed;			//�����ٶ�
	float _distance;		//��������
	Vec3 _spos;				//������ʼ������
	Vec3 _epos;				//����������
};

class Arrow :virtual protected Weapons
{
public:
	CREATE_WEAPON(Arrow);
	virtual void attack();
};

class Bomb :virtual protected Weapons
{
public:
	CREATE_WEAPON(Bomb);
	virtual void attack();
};

class Dart :virtual protected Weapons
{
public:
	CREATE_WEAPON(Dart);
	virtual void attack();
};


#endif