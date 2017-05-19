//实现各类武器的生成与控制

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
	/* 获取武器所属人物 */
	virtual void* getOwner() { return _owner; }
	/* 获取攻击力 */
	virtual float getPower() { return _power; }
	/* 获取攻击速度 */
	virtual float getSpeed() { return _speed; }
	/* 获取起始点坐标 */
	virtual Vec3 getSpos() { return _spos; }
	/* 获取目标点坐标 */
	virtual Vec3 getEpos() { return _epos; }
	virtual void attack() = 0;
protected:
	/* 初始化方法 */
	virtual bool init(void *owner, float power, float speed, float distance, Vec3 spos, Vec3 epos);
private:
	void *_owner;			//武器所属人物
	float _power;			//攻击力
	float _speed;			//攻击速度
	float _distance;		//攻击距离
	Vec3 _spos;				//攻击起始点坐标
	Vec3 _epos;				//攻击点坐标
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