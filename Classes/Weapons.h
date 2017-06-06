//实现各类武器的生成与控制

#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

/* 类声明，不能引入那个头文件，否则会造成无限引入 */
class Character;
class Weapons : public PhysicsSprite3D
{
public:
	Weapons();
	~Weapons();
	/* 获取武器所属人物 */
	virtual void* getOwner() const { return _owner; }
	/* 获取攻击力 */
	virtual float getPower() const { return _power; }
	/* 获取攻击速度 */
	virtual float getSpeed() const { return _speed; }
	/* 获取起始点坐标 */
	virtual Vec3 getSpos() const { return _spos; }
	/* 获取目标点坐标 */
	virtual Vec3 getEpos() const { return _epos; }
	/* SET */
	virtual void setOwner(void * const &owner) { _owner = owner; }
	virtual void setPower(const float &power) { _power = power; }
	virtual void setSpeed(const float &speed) { _speed = speed; }
	virtual void setSpos(const Vec3 &spos) { _spos = spos; }
	virtual void setEpos(const Vec3 &epos) { _epos = epos; }
	/* 销毁 */
	virtual void destroy();
	/* 创建 */
	CREATE_FUNC(Weapons);
	/* 初始化属性 */
	virtual bool init();
	virtual void init(void * const &owner, const Vec3 &spos, const Vec3 &epos);
	/* 杀死敌人 */
	virtual void killCharacter(Character *const &character) const;
	/* 与场景碰撞 */
	virtual void collisionWithStage();
	/* 与武器碰撞 */
	virtual void collisionWithWeapon(Weapons *const &weapon);
	/* 与人物碰撞 */
	virtual void collisionWithCharacter(Character *const &character);
private:
	void update(float dt);
	void *_owner;			//武器所属人物
	float _power;			//攻击力
	float _speed;			//攻击速度
	Vec3 _spos;				//攻击起始点坐标
	Vec3 _epos;				//攻击点坐标
	bool _isDeleted;		//是否已经被删除（是否存在于缓存池中）
};

class Arrow :public Weapons
{
public:
	Arrow(void *owner, Vec3 spos, Vec3 epos);
	~Arrow();
	static Arrow* create(void *owner, Vec3 spos, Vec3 epos);
};

class Bomb :public Weapons
{
public:
	Bomb(void *owner, Vec3 spos, Vec3 epos);
	~Bomb();
	static Bomb* create(void *owner, Vec3 spos, Vec3 epos);
};

class Dart :public Weapons
{
public:
	Dart(void *owner, Vec3 spos, Vec3 epos);
	~Dart();
	static Dart* create(void *owner, Vec3 spos, Vec3 epos);
};

#endif