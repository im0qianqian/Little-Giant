#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

/* ȡ���ֵ */
#define max(x,y) (x>y?x:y)
/* ȡ��Сֵ */
#define min(x,y) (x>y?y:x)
/* �������� */
#define swap(x,y) {x+=y;y=x-y;x-=y;}

/* ����һ���������� */
#define CREATE_WEAPON(__TYPE__) \
static __TYPE__* create(void *owner, float power, float speed, float distance, float angle, Vec2 pos) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(owner,power,speed,distance,angle,pos)) \
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

#endif
