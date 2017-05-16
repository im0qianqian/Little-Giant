//实现各类武器的生成与控制

#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;

class Weapons :public Sprite
{
public:
	Weapons();
	~Weapons();
	void* getOwner() { return _owner; }
	virtual void attack() = 0;
protected:
	/* 初始化方法 */
	bool init(void *owner, float power, float speed, float distance, float angle, Vec2 pos);
private:
	void update(float dt);
	void *_owner;			//武器所属人物
	float _power;			//攻击力
	float _speed;			//攻击速度
	float _distance;		//攻击距离
	float _angle;			//攻击方向
	Vec2 _pos;				//移动后的坐标
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