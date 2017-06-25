//��ɫ�ࣺ������ҵĸ�����Ϸ����

#ifndef __Character_H__
#define __Character_H__

#include "cocos2d.h"
#include "ui\UISlider.h"
#include "ui\UILoadingBar.h"
#include "Global.h"
#include "physics3d\CCPhysics3D.h"
#include <thread>
#include <mutex>

USING_NS_CC;

using namespace cocos2d::ui;

class Weapons;
class Award;
class AIStateMachine;
class Character : public PhysicsSprite3D
{
public:
	class Attribute final
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
	virtual Attribute &getAttribute() { return _attribute; }
	/* ���� */
	virtual void attack(const Vec3 &pos);
	/* �����ʼ�� */
	virtual bool init() override;
	/* �����ʼ�� */
	virtual void initialization();
	/* ��������ײ */
	virtual void collisionWithWeapon(Weapons *const &weapon);
	/* �뽱����ײ */
	virtual void collisionWithAward(Award *const &award);
	/* ��ǽ����ײ */
	virtual void collisionWithStage();
	/* �Ƿ����� */
	virtual bool isDie() const { return _isDie; }
	/* ���������ƶ��������� */
	virtual void setDirection(const Vec3 &direction) { _direction = direction; }
	/* ��ȡ�����ƶ��������� */
	virtual Vec3 getDirection() { return _direction; }
protected:
	/* �ƶ� */
	virtual void move();
	/* ���� */
	virtual void die();
	/* ��ȡ������ */
	virtual mutex &getThreadMutex() { return _threadMutex; }
	/* ������������ */
	virtual void setTopName(const string &name) { _topName->setString(name); }
	/* �ܵ��������� */
	virtual void beAttacked(Weapons *const &weapon);
private:
	/* �� update �йصĺ��� */
	virtual void update(float dt) override;
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
	unsigned int _lastAttackTime;	//�ϴι���ʱ��
	WeaponType _weaponType;	//��������
	Attribute _attribute;	//���Լӳ�
	bool _isDie;			//�����Ƿ�����
	Slider* _hpSlider;		//����Ѫ����
	Label* _topName;		//����ͷ��������
	Vec3 _direction;		//�����ƶ���������
	mutex _threadMutex;		//�߳���
};

class PlayerCharacter:public Character
{
public:
	CREATE_FUNC(PlayerCharacter);
	virtual void initialization() override;
private:
	/* �������� */
	virtual void die() override;
	virtual void moveModule() override;
};

class EnemyCharacter :public Character
{
public:
	EnemyCharacter();
	CREATE_FUNC(EnemyCharacter);
	virtual void initialization() override;
	virtual void collisionWithStage() override;
	AIStateMachine *getAIStateMachine() { return _aiMachine; }
protected:
	/* AI�ܵ����� */
	virtual void beAttacked(Weapons *const &weapon) override;
private:
	/* ������������ */
	virtual void die() override;
	virtual void moveModule() override;
	
	AIStateMachine *_aiMachine;	//AIϵͳ
};
#endif