//��ɫ�ࣺ������ҵĸ�����Ϸ����

#ifndef __Character_H__
#define __Character_H__

#include "cocos2d.h"
#include "Attribute.h"

USING_NS_CC;

enum WeaponType
{
	kWeaponArrow,
	kWeaponBomb,
	kWeaponDart
};

class Character :public Sprite3D
{
public:
	Character();
	~Character();
	/* ����/�������� */
	void addLifeValue(float add);
	/* ���Ӿ���ֵ */
	void addExperience(int add);
	/* ���ӷ��� */
	void addSorce(int add);
	/* ��ȡ��ǰ����ֵ */
	float getLifeValue() { return _lifeValue; }
	/* ��ȡ��ǰ����ֵ */
	int getExperience() { return _experience; }
	/* ��ȡ��ǰ�÷� */
	int getSorce() { return _sorce; }
	/* ��ȡ��ǰ�������� */
	Attribute *getAttribute() { return _attribute; }
	/* ���� */
	void attack();
	/* ���� */
	void die();
private:
	float _lifeValue;		//��������ֵ
	int _experience;		//��ǰ���о���
	int _sorce;				//��ǰ�÷�
	WeaponType _weaponType;	//��������
	Attribute _attribute;	//���Լӳ�
	Vec3 _pos;				//�����ƶ��������
	bool _isDie;				//�����Ƿ�����
	
};
#endif