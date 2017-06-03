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
const auto SCREEN_WIDTH = 640;
const auto SCREEN_HEIGHT = 960;
const auto FORM_NAME = "Arrow.io";

const auto WORLD_LENGTH = 100;	//���糤��
const auto WORLD_WIDTH = 100;	//������
const auto WORLD_HEIGHT = 1;		//����߶�

/* �����ʼ����ֵ */
const float INITIAL_LIFE_VALUE = 100;


enum GlobalType
{
	kGlobalStage,
	kGlobalCharacter,
	kGlobalWeapon
};

/* �ж� a �� b �Ƿ�ֱ�����ĳ���ֶ��� */
#define gObjectEqual(a,b,_a,_b) ((a==_a&&b==_b)||(a==_b&&b==_a))

// ����ʹ��
#include <iostream>
using namespace std;

#endif
