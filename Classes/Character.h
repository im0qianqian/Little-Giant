//��ɫ�ࣺ������ҵĸ�����Ϸ����

#ifndef __Character_H__
#define __Character_H__

#include "cocos2d.h"
#include "ui\UISlider.h"
#include "ui\UILoadingBar.h"
#include "Global.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

using namespace cocos2d::ui;

class Weapons;
class Character :public PhysicsSprite3D
{
public:
	virtual class Attribute
	{
	public:
		Attribute();
		~Attribute();
		/* ���ӹ����� */
		virtual void addAttackDamage(const float &add);
		/* ���ӹ����ٶ� */
		virtual void addAttackSpeed(const float &add);
		/* �����ƶ��ٶ� */
		virtual void addMovingSpeed(const float &add);
		/* ���Ӿ����ȡ���� */
		virtual void addEmpiricalAcquisition(const float &add);
		/* ���ӷ����� */
		virtual void addDefensiveForce(const float &add);
		/* ���ӻָ����� */
		virtual void addRestoringAbility(const float &add);
		/* ��ʱ���ԣ�������Ұ */
		virtual void addView();
		/* ��ʱ���ԣ����ӱ�С */
		virtual void addSmall();
		/* ��ʱ���ԣ����Ӵ�ʯ */
		virtual void addMagnet();
		/* ��ʱ���ԣ��ָ���Ұ */
		virtual void delView();
		/* ��ʱ���ԣ��ָ���� */
		virtual void delSmall();
		/* ��ʱ���ԣ�ȥ����ʯ */
		virtual void delMagnet();
		/* ������ʱ��������ʱ�� */
		virtual void setDuration(float add);
		/* GET */
		virtual float getAttackDamage() const { return _attackDamage; }
		virtual float getAttackSpeed() const { return _attackSpeed; }
		virtual float getMovingSpeed() const { return _movingSpeed; }
		virtual float getEmpiricalAcquisition() const { return _empiricalAcquisition; }
		virtual float getDefensiveForce() const { return _defensiveForce; }
		virtual float getRestoringAbility() const { return _restoringAbility; }
		/* ��ʼ�� */
		virtual void init();
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
		virtual enum TemporaryType
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
	virtual void addLifeValue(const float &add);
	/* ���Ӿ���ֵ */
	virtual void addExperience(const int &add);
	/* ���ӷ��� */
	virtual void addSorce(const int &add);
	/* ��ȡ��������Ⱥ�� */
	virtual int getDept() const { return _dept; }
	/* ��ȡ��ǰ����ֵ */
	virtual float getLifeValue() const { return _lifeValue; }
	/* ��ȡ��ǰ����ֵ */
	virtual int getExperience() const { return _experience; }
	/* ��ȡ��ǰ�÷� */
	virtual int getSorce() const { return _sorce; }
	/* ��������Ⱥ�� */
	virtual void setDept(const int &dept) { _dept = dept; }
	/* ��ȡ��ǰ�������� */
	virtual Attribute getAttribute() const { return _attribute; }
	/* ���� */
	virtual void attack(const Vec3 &pos);
	/* �����ʼ�� */
	virtual bool init();
	/* �����ʼ�� */
	virtual void initialization();
	/* ��������ײ */
	virtual void collisionWithWeapon(Weapons *const &weapon);
	/* �Ƿ����� */
	virtual bool isDie() const { return _isDie; }
protected:
	/* �ƶ� */
	virtual void move(const Vec3 &pos);
	/* ���� */
	virtual void die();
private:
	/* �ܵ��������� */
	virtual void beAttacked(Weapons *const &weapon);
	/* �� update �йصĺ��� */
	void update(float dt);
	/* �����ƶ�ģ�� */
	virtual void moveModule() = 0;
	/* ��⵱ǰ״���������Ƿ�������� */
	virtual bool detectionStatus();
	/* ������ʾ�йأ�����Ѫ���� */
	virtual void createHpBar();

	int _dept;				//��������Ⱥ��
	float _lifeValue;		//��������ֵ
	int _experience;		//��ǰ���о���
	int _sorce;				//��ǰ�÷�
	WeaponType _weaponType;	//��������
	Attribute _attribute;	//���Լӳ�
	bool _isDie;			//�����Ƿ�����
	Slider* _hpSlider;		//����Ѫ����
};

class PlayerCharacter:public Character
{
public:
	CREATE_FUNC(PlayerCharacter);
	void initialization();
private:
	/* �������� */
	void die();
	void moveModule();
};

class EnemyCharacter :public Character
{
public:
	CREATE_FUNC(EnemyCharacter);
	void initialization();
private:
	/* ������������ */
	void die();
	void moveModule();
};
#endif