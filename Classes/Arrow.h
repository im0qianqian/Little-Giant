#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"

USING_NS_CC;

enum AttackType	//��������
{
	AStraight,	//ֱ�߹���
	ARing,		//���ι���
	ACurve		//���߹���
};

class Arrow :public Sprite
{
public:
	Arrow();
	~Arrow();
	/* ���� */
	Arrow* create(void *owner, float power, float speed, float distance, Vec2 pos, AttackType attackType, float direction);
	void* getOwner();
private:
	/* ��ʼ������ */
	bool init(void *owner, float power, float speed, float distance, Vec2 pos, AttackType attackType, float direction);
	void update(float dt);

	void *_owner;			//��ʸ��������
	float _power;			//������
	float _speed;			//�����ٶ�
	float _distance;		//��������
	Vec2 _initialPosition;	//��ʸ��ʼλ��
	float _direction;		//��������
	AttackType _attackType;	//��������
};
#endif