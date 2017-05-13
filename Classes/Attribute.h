#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

USING_NS_CC;

/*
 * View ���λ
 * Small �м�λ
 * Magnet ���λ
 * 3λ�����Ʊ�ʾ����״̬
 */
enum Temporary
{
	Nothing,		//����ʱ����
	View,			//��Ұ
	Small,			//�����С
	ViewSmall,		//��Ұ+��С
	Magnet,			//��ʯЧ��
	MagnetView,		//��ʯ+��Ұ
	MagnetSmall,	//��ʯ+��С
	MagnetSmallView	//��ʯ+��С+��Ұ
};

/* ���Լӳ��� */
class Attribute:public Sprite
{
public:
	Attribute();
	~Attribute();
	Attribute* create();
private:
	void update(float dt);
	float _attackDamage;			//�������ӳ�
	float _attackRange;				//��̼ӳ�
	float _attackSpeed;				//�����ٶȼӳ�
	float _movingSpeed;				//�ƶ��ٶȼӳ�
	float _empiricalAcquisition;	//�����ȡ�ӳ�
	float _defensiveForce;			//�������ӳ�
	float _restoringAbility;		//�ָ������ӳ�
	float _duration;				//��ʱ��������ʱ��
};
#endif
