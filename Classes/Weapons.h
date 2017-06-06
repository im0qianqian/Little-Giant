//ʵ�ָ������������������

#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

/* �����������������Ǹ�ͷ�ļ������������������� */
class Character;
class Weapons : public PhysicsSprite3D
{
public:
	Weapons();
	~Weapons();
	/* ��ȡ������������ */
	virtual void* getOwner() const { return _owner; }
	/* ��ȡ������ */
	virtual float getPower() const { return _power; }
	/* ��ȡ�����ٶ� */
	virtual float getSpeed() const { return _speed; }
	/* ��ȡ��ʼ������ */
	virtual Vec3 getSpos() const { return _spos; }
	/* ��ȡĿ������� */
	virtual Vec3 getEpos() const { return _epos; }
	/* SET */
	virtual void setOwner(void * const &owner) { _owner = owner; }
	virtual void setPower(const float &power) { _power = power; }
	virtual void setSpeed(const float &speed) { _speed = speed; }
	virtual void setSpos(const Vec3 &spos) { _spos = spos; }
	virtual void setEpos(const Vec3 &epos) { _epos = epos; }
	/* ���� */
	virtual void destroy();
	/* ���� */
	CREATE_FUNC(Weapons);
	/* ��ʼ������ */
	virtual bool init();
	virtual void init(void * const &owner, const Vec3 &spos, const Vec3 &epos);
	/* ɱ������ */
	virtual void killCharacter(Character *const &character) const;
	/* �볡����ײ */
	virtual void collisionWithStage();
	/* ��������ײ */
	virtual void collisionWithWeapon(Weapons *const &weapon);
	/* ��������ײ */
	virtual void collisionWithCharacter(Character *const &character);
private:
	void update(float dt);
	void *_owner;			//������������
	float _power;			//������
	float _speed;			//�����ٶ�
	Vec3 _spos;				//������ʼ������
	Vec3 _epos;				//����������
	bool _isDeleted;		//�Ƿ��Ѿ���ɾ�����Ƿ�����ڻ�����У�
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