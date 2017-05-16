//�����ࣺ��Ӧ����������Եļӳ�

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

/*
* View ���λ
* Small �м�λ
* Magnet ���λ
*/
enum TemporaryType
{
	kTemporaryNone = 0x00,
	kTemporaryView = 0x01,
	kTemporarySmall = 0x02,
	kTemporaryMagnet = 0x04
};

/* ���Լӳ��� */
class Attribute
{
public:
	Attribute();
	~Attribute();
	/* ����һ�����Զ��� */
	static Attribute* create();
	/* ���ӹ����� */
	void addAttackDamage(float add);
	/* ������� */
	void addAttackRange(float add);
	/* ���ӹ����ٶ� */
	void addAttackSpeed(float add);
	/* �����ƶ��ٶ� */
	void addMovingSpeed(float add);
	/* ���Ӿ����ȡ���� */
	void addEmpiricalAcquisition(float add);
	/* ���ӷ����� */
	void addDefensiveForce(float add);
	/* ���ӻָ����� */
	void addRestoringAbility(float add);
	/* ��ʱ���ԣ�������Ұ */
	void addView();
	/* ��ʱ���ԣ����ӱ�С */
	void addSmall();
	/* ��ʱ���ԣ����Ӵ�ʯ */
	void addMagnet();
	/* ��ʱ���ԣ��ָ���Ұ */
	void delView();
	/* ��ʱ���ԣ��ָ���� */
	void delSmall();
	/* ��ʱ���ԣ�ȥ����ʯ */
	void delMagnet();
	/* ������ʱ��������ʱ�� */
	void setDuration(float add);
private:
	float _attackDamage;			//�������ӳ�
	float _attackRange;				//��̼ӳ�
	float _attackSpeed;				//�����ٶȼӳ�
	float _movingSpeed;				//�ƶ��ٶȼӳ�
	float _empiricalAcquisition;	//�����ȡ�ӳ�
	float _defensiveForce;			//�������ӳ�
	float _restoringAbility;		//�ָ������ӳ�
	short int _temporary;			//��ʱ��������
	float _duration;				//��ʱ��������ʱ��
};
#endif
