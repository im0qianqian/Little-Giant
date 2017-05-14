#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Attribute.h"

USING_NS_CC;

enum ArrowType
{

};

class CharActer :public Sprite
{
public:
private:
	float _lifeValue;		//人物生命值
	int _experience;		//当前已有经验
	int _sorce;				//当前得分
	ArrowType _arrowType;	//武器类型
	Attribute _attribute;	//属性加成
};
#endif