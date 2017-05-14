#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"

USING_NS_CC;

enum AttackType	//攻击类型
{
	AStraight,	//直线攻击
	ARing,		//环形攻击
	ACurve		//曲线攻击
};

class Arrow :public Sprite
{
public:
	Arrow();
	~Arrow();
	/* 创建 */
	Arrow* create(void *owner, float power, float speed, float distance, Vec2 pos, AttackType attackType, float direction);
	void* getOwner();
private:
	/* 初始化方法 */
	bool init(void *owner, float power, float speed, float distance, Vec2 pos, AttackType attackType, float direction);
	void update(float dt);

	void *_owner;			//箭矢所属人物
	float _power;			//攻击力
	float _speed;			//攻击速度
	float _distance;		//攻击距离
	Vec2 _initialPosition;	//箭矢起始位置
	float _direction;		//攻击方向
	AttackType _attackType;	//攻击类型
};
#endif