//角色类：保持玩家的各项游戏属性

#ifndef __Character_H__
#define __Character_H__

#include "cocos2d.h"
#include "Attribute.h"
#include "Weapons.h"

USING_NS_CC;

class Character :public Sprite3D
{
public:
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
	Attribute *getAttribute() { return _attribute; }
	/* 攻击 */
	void attack();
	/* 死亡 */
	void die();
private:
	float _lifeValue;		//人物生命值
	int _experience;		//当前已有经验
	int _sorce;				//当前得分
	WeaponType _weaponType;	//武器类型
	Attribute* _attribute;	//属性加成
	Vec3 _pos;				//人物移动后的坐标
	bool _isDie;			//人物是否死亡
	
};
#endif