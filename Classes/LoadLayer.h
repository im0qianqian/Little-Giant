#ifndef __LoadLayer_H__
#define __LoadLayer_H__

#include "cocos2d.h"
using namespace cocos2d;

class LoadLayer:public cocos2d::Layer
{
public :
	LoadLayer();
	~LoadLayer();
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LoadLayer);
	void LoadingCallback();
private:
	ProgressTimer *timer;
	int totalImage;
	int loadImage;
	Label *percentLabel;
	Label *loadLabel;
};
#endif