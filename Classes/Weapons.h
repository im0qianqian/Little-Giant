//ʵ�ָ������������������

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
	void* getOwner();
	virtual void attack() = 0;
protected:
	/* ��ʼ������ */
	bool init(void *owner, float power, float speed, float distance, float angle, Vec2 pos);
private:
	void update(float dt);
	void *_owner;			//������������
	float _power;			//������
	float _speed;			//�����ٶ�
	float _distance;		//��������
	float _angle;			//��������
	Vec2 _pos;				//������ʼλ��
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