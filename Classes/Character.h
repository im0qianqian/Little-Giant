//��ɫ�ࣺ������ҵĸ�����Ϸ����

#ifndef __Character_H__
#define __Character_H__

#include "cocos2d.h"
#include "ui\UISlider.h"
#include "Global.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

using namespace cocos2d::ui;

class Weapons;
class Character :public PhysicsSprite3D
{
public:
	class Attribute
	{
	public:
		Attribute();
		~Attribute();
		/* ���ӹ����� */
		void addAttackDamage(const float &add);
		/* ���ӹ����ٶ� */
		void addAttackSpeed(const float &add);
		/* �����ƶ��ٶ� */
		void addMovingSpeed(const float &add);
		/* ���Ӿ����ȡ���� */
		void addEmpiricalAcquisition(const float &add);
		/* ���ӷ����� */
		void addDefensiveForce(const float &add);
		/* ���ӻָ����� */
		void addRestoringAbility(const float &add);
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
		/* GET */
		float getAttackDamage() const { return _attackDamage; }
		float getAttackSpeed() const { return _attackSpeed; }
		float getMovingSpeed() const { return _movingSpeed; }
		float getEmpiricalAcquisition() const { return _empiricalAcquisition; }
		float getDefensiveForce() const { return _defensiveForce; }
		float getRestoringAbility() const { return _restoringAbility; }
		/* ��ʼ�� */
		void init();
	private:
		float _attackDamage;			//�������ӳ�
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
	Character();
	~Character();
	/* ����/�������� */
	void addLifeValue(const float &add);
	/* ���Ӿ���ֵ */
	void addExperience(const int &add);
	/* ���ӷ��� */
	void addSorce(const int &add);
	/* ��ȡ��������Ⱥ�� */
	int getDept() const { return _dept; }
	/* ��ȡ��ǰ����ֵ */
	float getLifeValue() const { return _lifeValue; }
	/* ��ȡ��ǰ����ֵ */
	int getExperience() const { return _experience; }
	/* ��ȡ��ǰ�÷� */
	int getSorce() const { return _sorce; }
	/* ��������Ⱥ�� */
	void setDept(const int &dept) { _dept = dept; }
	/* ��ȡ��ǰ�������� */
	Attribute getAttribute() const { return _attribute; }
	/* ���� */
	void attack(const Vec3 &pos);
	virtual bool init();
	CREATE_FUNC(Character);
	/* �����ʼ�� */
	void initialization();
	/* ��������ײ */
	void collisionWithWeapon(Weapons *const &weapon);
private:
	/* �ܵ��������� */
	void beAttacked(Weapons *const &weapon);
	/* ���� */
	void die();
	/* �ƶ� */
	void move(const Vec3 &pos);
	/* �� update �йصĺ��� */
	virtual void update(float dt);

	int _dept;				//��������Ⱥ��
	float _lifeValue;		//��������ֵ
	int _experience;		//��ǰ���о���
	int _sorce;				//��ǰ�÷�
	WeaponType _weaponType;	//��������
	Attribute _attribute;	//���Լӳ�
	bool _isDie;			//�����Ƿ�����
	Slider* _hpSlider;		//����Ѫ����
};

#endif