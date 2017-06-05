#ifndef __AWARD_H__
#define __AWARD_H__

#include "cocos2d.h"
#include "Character.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Award :public PhysicsSprite3D
{
public:
	Award();
	~Award();
	virtual bool init();
	/* 初始化方法 */
	void initialization();
	/* 销毁 */
	void destroy();
	/* 创建 */
	CREATE_FUNC(Award);
	enum AwardType
	{
		kAwardHP,
		kAwardEXP
	};
	/* 将奖励应用于人物 */
	void applyToCharacter(Character *const &character);
private:
	
	/* 随机生成奖励类型 */
	void randomType();
	AwardType _awardType;	//奖励类型
	bool _isDeleted;		//是否被删除
};
#endif