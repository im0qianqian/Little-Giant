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
	float _lifeValue;		//��������ֵ
	int _experience;		//��ǰ���о���
	int _sorce;				//��ǰ�÷�
	ArrowType _arrowType;	//��������
	Attribute _attribute;	//���Լӳ�
};
#endif