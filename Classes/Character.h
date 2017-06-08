//角色类：保持玩家的各项游戏属性

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
	class Attribute
	{
	public:
		Attribute();
		~Attribute();
		/* 增加攻击力 */
		void addAttackDamage(const float &add);
		/* 增加攻击速度 */
		void addAttackSpeed(const float &add);
		/* 增加移动速度 */
		void addMovingSpeed(const float &add);
		/* 增加经验获取倍数 */
		void addEmpiricalAcquisition(const float &add);
		/* 增加防御力 */
		void addDefensiveForce(const float &add);
		/* 增加恢复能力 */
		void addRestoringAbility(const float &add);
		/* 临时属性：增加视野 */
		void addView();
		/* 临时属性：增加变小 */
		void addSmall();
		/* 临时属性：增加磁石 */
		void addMagnet();
		/* 临时属性：恢复视野 */
		void delView();
		/* 临时属性：恢复变大 */
		void delSmall();
		/* 临时属性：去除磁石 */
		void delMagnet();
		/* 更改临时能力持续时间 */
		void setDuration(float add);
		/* GET */
		float getAttackDamage() const { return _attackDamage; }
		float getAttackSpeed() const { return _attackSpeed; }
		float getMovingSpeed() const { return _movingSpeed; }
		float getEmpiricalAcquisition() const { return _empiricalAcquisition; }
		float getDefensiveForce() const { return _defensiveForce; }
		float getRestoringAbility() const { return _restoringAbility; }
		/* 初始化 */
		void init();
	private:
		float _attackDamage;			//攻击力加成
		float _attackSpeed;				//攻击速度加成
		float _movingSpeed;				//移动速度加成
		float _empiricalAcquisition;	//经验获取加成
		float _defensiveForce;			//防御力加成
		float _restoringAbility;		//恢复能力加成
		/*
		 * View 最低位
		 * Small 中间位
		 * Magnet 最高位
		 */
		enum TemporaryType
		{
			kTemporaryNone = 0x00,
			kTemporaryView = 0x01,
			kTemporarySmall = 0x02,
			kTemporaryMagnet = 0x04
		};
		short int _temporary;			//临时属性类型
		float _duration;				//临时能力持续时间
	};
	Character();
	~Character();
	/* 增加/减少生命 */
	void addLifeValue(const float &add);
	/* 增加经验值 */
	void addExperience(const int &add);
	/* 增加分数 */
	void addSorce(const int &add);
	/* 获取人物所属群落 */
	int getDept() const { return _dept; }
	/* 获取当前生命值 */
	float getLifeValue() const { return _lifeValue; }
	/* 获取当前经验值 */
	int getExperience() const { return _experience; }
	/* 获取当前得分 */
	int getSorce() const { return _sorce; }
	/* 更改人物群落 */
	void setDept(const int &dept) { _dept = dept; }
	/* 获取当前人物属性 */
	Attribute getAttribute() const { return _attribute; }
	/* 攻击 */
	void attack(const Vec3 &pos);
	virtual bool init();
	CREATE_FUNC(Character);
	/* 人物初始化 */
	void initialization();
	/* 与武器碰撞 */
	void collisionWithWeapon(Weapons *const &weapon);
	/* 是否死亡 */
	bool isDie() const { return _isDie; }
private:
	/* 受到武器攻击 */
	void beAttacked(Weapons *const &weapon);
	/* 死亡 */
	void die();
	/* 移动 */
	void move(const Vec3 &pos);
	/* 与 update 有关的函数 */
	virtual void update(float dt);
	/* 界面显示有关，创建血量条 */
	void createHpBar();
	int _dept;				//人物所属群落
	float _lifeValue;		//人物生命值
	int _experience;		//当前已有经验
	int _sorce;				//当前得分
	WeaponType _weaponType;	//武器类型
	Attribute _attribute;	//属性加成
	bool _isDie;			//人物是否死亡
	Slider* _hpSlider;		//人物血量条
};

#endif