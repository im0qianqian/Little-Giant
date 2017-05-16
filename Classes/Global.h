//游戏全局用具

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

/* 取最大值 */
#define max(x,y) (x>y?x:y)
/* 取最小值 */
#define min(x,y) (x>y?y:x)
/* 两数交换 */
#define swap(x,y) {x+=y;y=x-y;x-=y;}

/* 创建一个武器对象 */
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

/* 全局常量设置 */
const auto SCREEN_WIDTH = 640;
const auto SCREEN_HEIGHT = 960;
const auto FORM_NAME = "Arrow.io";

/* 人物初始生命值 */
const float INITIAL_LIFE_VALUE = 100;
#endif
