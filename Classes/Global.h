//游戏全局用具

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

/* 取最大值 */
#define max(x,y) (x>y?x:y)
/* 取最小值 */
#define min(x,y) (x>y?y:x)

/* 创建一个武器对象 */
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

/* 全局常量设置 */
#define SCREEN_WIDTH			640			//屏幕高度
#define SCREEN_HEIGHT			960			//屏幕宽度
#define SCREEN_FORM_NAME		"Arrow.io"	//窗口标题

#define WORLD_LENGTH			100			//世界长度
#define WORLD_WIDTH				100			//世界宽度
#define WORLD_HEIGHT			1			//世界高度

#define CHARACTER_CACHE_SIZE	50			//人物对象缓存池大小
#define WEAPONS_CACHE_SIZE		100			//武器对象缓存池大小

#define INITIAL_LIFE_VALUE		100.f		//人物初始生命值

#define ELEMENT_LENGTH  2     //组成元素的长度
#define ELEMENT_WIDTH   2     //组成元素的宽度
#define ELEMENT_HEIGHT  10     //墙的高度


enum GlobalType
{
	kGlobalStage,
	kGlobalCharacter,
	kGlobalWeapon
};

/* 判断 a 与 b 是否分别属于某两种对象 */
#define gObjectEqual(a,b,_a,_b) ((a==_a&&b==_b)||(a==_b&&b==_a))

// 调试使用
#include <iostream>
using namespace std;

#endif
