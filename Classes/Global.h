//��Ϸȫ���þ�

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

/* ȡ���ֵ */
#define max(x,y) (x>y?x:y)
/* ȡ��Сֵ */
#define min(x,y) (x>y?y:x)

/* ����һ���������� */
#define CREATE_WEAPON(__TYPE__) \
static __TYPE__* create(void *owner, float power, float speed, Vec3 spos, Vec3 epos) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(owner,power,speed,spos,epos)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

/* ȫ�ֳ������� */
#define SCREEN_WIDTH			640			//��Ļ�߶�
#define SCREEN_HEIGHT			960			//��Ļ���
#define SCREEN_FORM_NAME		"Arrow.io"	//���ڱ���

#define WORLD_LENGTH			208			//���糤��
#define WORLD_WIDTH				208			//������
#define WORLD_HEIGHT			1			//����߶�
#define ELEMENT_HEIGHT			20			//ǽ�ĸ߶�

#define CHARACTER_CACHE_SIZE	50			//������󻺴�ش�С
#define WEAPONS_CACHE_SIZE		100			//�������󻺴�ش�С
#define AWARD_CACHE_SIZE		50			//�������󻺴�ش�С

#define INITIAL_LIFE_VALUE		100.f		//�����ʼ����ֵ

#define MAPS_FILE_LENGTH		52			//��ͼ�ļ���
#define MAPS_FILE_WIDTH			52			//��ͼ�ļ���


enum GlobalType
{
	kGlobalStage,
	kGlobalCharacter,
	kGlobalWeapon,
	kGlobalAward
};

enum WeaponType
{
	kWeaponArrow,
	kWeaponBomb,
	kWeaponDart
};

/* �ж� a �� b �Ƿ�ֱ�����ĳ���ֶ��� */
#define gObjectEqual(a,b,_a,_b) ((a==_a&&b==_b)||(a==_b&&b==_a))

// ����ʹ��
#include <iostream>
using namespace std;

#endif
