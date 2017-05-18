//角色类：保持玩家的各项游戏属性

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
		/* 增加攻击力 */
		void addAttackDamage(float add);
		/* 增加射程 */
		void addAttackRange(float add);
		/* 增加攻击速度 */
		void addAttackSpeed(float add);
		/* 增加移动速度 */
		void addMovingSpeed(float add);
		/* 增加经验获取倍数 */
		void addEmpiricalAcquisition(float add);
		/* 增加防御力 */
		void addDefensiveForce(float add);
		/* 增加恢复能力 */
		void addRestoringAbility(float add);
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
	private:
		float _attackDamage;			//攻击力加成
		float _attackRange;				//射程加成
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
	virtual bool init();
	Character();
	~Character();
	/* 增加/减少生命 */
	void addLifeValue(float add);
	/* 增加经验值 */
	void addExperience(int add);
	/* 增加分数 */
	void addSorce(int add);
	/* 获取当前生命值 */
	float getLifeValue() { return _lifeValue; }
	/* 获取当前经验值 */
	int getExperience() { return _experience; }
	/* 获取当前得分 */
	int getSorce() { return _sorce; }
	/* 获取当前人物属性 */
	Attribute getAttribute() { return _attribute; }
	/* 攻击 */
	void attack();
	/* 死亡 */
	void die();
private:
	float _lifeValue;		//人物生命值
	int _experience;		//当前已有经验
	int _sorce;				//当前得分
	WeaponType _weaponType;	//武器类型
	Attribute _attribute;	//属性加成
	Vec3 _pos;				//人物移动后的坐标
	bool _isDie;			//人物是否死亡
};


/* 属性加成类 */

#endif