#ifndef __AWARD_H__
#define __AWARD_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Character;
class Award :public PhysicsSprite3D
{
public:
	Award();
	~Award();
	virtual bool init();
	/* ��ʼ������ */
	void initialization();
	/* ���� */
	CREATE_FUNC(Award);
	/* ��������ײ */
	void collisionWithCharacter(Character *const &character);
private:
	enum AwardType
	{
		kAwardHP,
		kAwardEXP
	};
	/* ���� */
	void destroy();
	/* ������Ӧ�������� */
	void applyToCharacter(Character *const &character);
	/* ������ɽ������� */
	void randomType();
	AwardType _awardType;	//��������
	bool _isDeleted;		//�Ƿ�ɾ��
};
#endif