#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "cocos2d.h"

USING_NS_CC;

#define max(x,y) (x>y?x:y)
#define min(x,y) (x>y?y:x)
#define swap(x,y) {x+=y;y=x-y;x-=y;}

#endif