#ifndef __AWARD_H__
#define __AWARD_H__

#include "cocos2d.h"
#include "Character.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Award :public PhysicsSprite3D
{
public:
	Award();
	~Award();
	virtual bool init();
	/* ��ʼ������ */
	void initialization();
	/* ���� */
	void destroy();
	/* ���� */
	CREATE_FUNC(Award);
	enum AwardType
	{
		kAwardHP,
		kAwardEXP
	};
	/* ������Ӧ�������� */
	void applyToCharacter(Character *const &character);
private:
	
	/* ������ɽ������� */
	void randomType();
	AwardType _awardType;	//��������
	bool _isDeleted;		//�Ƿ�ɾ��
};
#endif