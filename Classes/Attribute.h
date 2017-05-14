#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

/*
 * View 最低位
 * Small 中间位
 * Magnet 最高位
 * 3位二进制表示六种状态
 */
enum Temporary
{
	TNothing,		//无临时属性
	TView,			//视野
	TSmall,			//人物变小
	TViewSmall,		//视野+变小
	TMagnet,			//磁石效果
	TMagnetView,		//磁石+视野
	TMagnetSmall,	//磁石+变小
	TMagnetSmallView	//磁石+变小+视野
};

/* 属性加成类 */
class Attribute:public Sprite
{
public:
	Attribute();
	~Attribute();
	Attribute* create();
private:
	void update(float dt);
	float _attackDamage;			//攻击力加成
	float _attackRange;				//射程加成
	float _attackSpeed;				//攻击速度加成
	float _movingSpeed;				//移动速度加成
	float _empiricalAcquisition;	//经验获取加成
	float _defensiveForce;			//防御力加成
	float _restoringAbility;		//恢复能力加成
	float _duration;				//临时能力持续时间
};
#endif
