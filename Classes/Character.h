//��ɫ�ࣺ������ҵĸ�����Ϸ����

#ifndef __Character_H__
#define __Character_H__

#include "cocos2d.h"
#include "Weapons.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Character :public PhysicsSprite3D
{
public:
	class Attribute
	{
	public:
		Attribute();
		~Attribute();
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
		short int _temporary;			//��ʱ��������
		float _duration;				//��ʱ��������ʱ��
	};
	virtual bool init();
	Character();
	~Character();
	/* ����/�������� */
	void addLifeValue(float add);
	/* ���Ӿ���ֵ */
	void addExperience(int add);
	/* ���ӷ��� */
	void addSorce(int add);
	/* ��ȡ��ǰ����ֵ */
	float getLifeValue() { return _lifeValue; }
	/* ��ȡ��ǰ����ֵ */
	int getExperience() { return _experience; }
	/* ��ȡ��ǰ�÷� */
	int getSorce() { return _sorce; }
	/* ��ȡ��ǰ�������� */
	Attribute getAttribute() { return _attribute; }
	/* ���� */
	void attack();
	/* ���� */
	void die();
private:
	float _lifeValue;		//��������ֵ
	int _experience;		//��ǰ���о���
	int _sorce;				//��ǰ�÷�
	WeaponType _weaponType;	//��������
	Attribute _attribute;	//���Լӳ�
	Vec3 _pos;				//�����ƶ��������
	bool _isDie;			//�����Ƿ�����
};


/* ���Լӳ��� */

#endif