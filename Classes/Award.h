#ifndef __AWARD_H__
#define __AWARD_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Character;
class Award :public PhysicsSprite3D
{
public:
	Award();
	~Award();
	virtual bool init();
	/* 初始化方法 */
	void initialization();
	/* 创建 */
	CREATE_FUNC(Award);
	/* 与人物碰撞 */
	void collisionWithCharacter(Character *const &character);
	/* 是否被删除 */
	bool isDeleted() const { return _isDeleted; }
private:
	enum AwardType
	{
		kAwardHP,
		kAwardEXP,
		kAwardSorce
	};
	/* 销毁 */
	void destroy();
	/* 将奖励应用于人物 */
	void applyToCharacter(Character *const &character);
	/* 随机生成奖励类型 */
	void randomType();

	AwardType _awardType;	//奖励类型
	bool _isDeleted;		//是否被删除
};
#endif