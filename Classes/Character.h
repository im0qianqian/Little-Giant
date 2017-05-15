//��ɫ�ࣺ������ҵĸ�����Ϸ����

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
	/* ����/�������� */
	void addLifeValue(float add);
	/* ���Ӿ���ֵ */
	void addExperience(int add);
	/* ���ӷ��� */
	void addSorce(int add);
	/* ��ȡ��ǰ����ֵ */
	float getLifeValue();
	/* ��ȡ��ǰ����ֵ */
	int getExperience();
	/* ��ȡ��ǰ�÷� */
	int getSorce();
	/* ��ȡ��ǰ�������� */
	
private:
	float _lifeValue;		//��������ֵ
	int _experience;		//��ǰ���о���
	int _sorce;				//��ǰ�÷�
	WeaponType _arrowType;	//��������
	Attribute _attribute;	//���Լӳ�
};
#endif