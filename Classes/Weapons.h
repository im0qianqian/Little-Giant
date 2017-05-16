//ʵ�ָ������������������

#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;

enum WeaponType
{
	kWeaponArrow,
	kWeaponBomb,
	kWeaponDart
};

class Weapons :public Sprite3D
{
public:
	Weapons();
	~Weapons();
	void* getOwner() { return _owner; }
	virtual void attack() = 0;
protected:
	/* ��ʼ������ */
	bool init(void *owner, float power, float speed, float distance, float angle, Vec3 pos);
private:
	void update(float dt);
	void *_owner;			//������������
	float _power;			//������
	float _speed;			//�����ٶ�
	float _distance;		//��������
	float _angle;			//��������
	Vec3 _pos;				//�ƶ��������
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