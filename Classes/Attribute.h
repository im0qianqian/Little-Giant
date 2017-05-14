#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

/* ���Լӳ��� */
class Attribute :public Sprite
{
public:
	Attribute();
	~Attribute();
	/* ����һ�����Զ��� */
	static Attribute* create(float attackDamage = 0, float attackRange = 0, float attackSpeed = 0, float movingSpeed = 0, float empiricalAcquisition = 0, float defensiveForce = 0, float restoringAbility = 0, short int temporary = 0, float duration = 0);
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
	void update(float dt);
	/* ��ʼ������ */
	bool Attribute::init(float attackDamage, float attackRange, float attackSpeed, float movingSpeed, float empiricalAcquisition, float defensiveForce, float restoringAbility, short int temporary, float duration);
	float _attackDamage;			//�������ӳ�
	float _attackRange;				//��̼ӳ�
	float _attackSpeed;				//�����ٶȼӳ�
	float _movingSpeed;				//�ƶ��ٶȼӳ�
	float _empiricalAcquisition;	//�����ȡ�ӳ�
	float _defensiveForce;			//�������ӳ�
	float _restoringAbility;		//�ָ������ӳ�
	/*
	 * View ���λ
	 * Small �м�λ
	 * Magnet ���λ
	 * 3λ�����Ʊ�ʾ����״̬ MSV
	 */
	short int _temporary;			//��ʱ��������
	float _duration;				//��ʱ��������ʱ��
};
#endif
