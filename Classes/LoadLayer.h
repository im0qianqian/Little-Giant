#ifndef __LOAD_LAYER_H__
#define __LOAD_LAYER_H__

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
	void loadingCallback();
private:
	ProgressTimer *_timer;
	int _totalImage;
	int _loadImage;
	Label *_percentLabel;
	Label *_loadLabel;
};
#endif