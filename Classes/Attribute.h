#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

/* 属性加成类 */
class Attribute :public Sprite
{
public:
	Attribute();
	~Attribute();
	/* 创建一个属性对象 */
	static Attribute* create(float attackDamage = 0, float attackRange = 0, float attackSpeed = 0, float movingSpeed = 0, float empiricalAcquisition = 0, float defensiveForce = 0, float restoringAbility = 0, short int temporary = 0, float duration = 0);
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
	void update(float dt);
	/* 初始化方法 */
	bool Attribute::init(float attackDamage, float attackRange, float attackSpeed, float movingSpeed, float empiricalAcquisition, float defensiveForce, float restoringAbility, short int temporary, float duration);
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
	 * 3位二进制表示八种状态 MSV
	 */
	short int _temporary;			//临时属性类型
	float _duration;				//临时能力持续时间
};
#endif
