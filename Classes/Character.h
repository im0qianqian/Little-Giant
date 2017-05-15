//角色类：保持玩家的各项游戏属性

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Attribute.h"

USING_NS_CC;

enum WeaponType
{
	WeaponType_Arrow,
	WeaponType_Bomb,
	WeaponType_Dart
};

class CharActer :public Sprite
{
public:
	/* 增加/减少生命 */
	void addLifeValue(float add);
	/* 增加经验值 */
	void addExperience(int add);
	/* 增加分数 */
	void addSorce(int add);
	/* 获取当前生命值 */
	float getLifeValue();
	/* 获取当前经验值 */
	int getExperience();
	/* 获取当前得分 */
	int getSorce();
	/* 获取当前武器类型 */
	
private:
	float _lifeValue;		//人物生命值
	int _experience;		//当前已有经验
	int _sorce;				//当前得分
	WeaponType _arrowType;	//武器类型
	Attribute _attribute;	//属性加成
};
#endif