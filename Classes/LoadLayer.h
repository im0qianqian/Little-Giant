#ifndef __LOAD_LAYER_H__
#define __LOAD_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class LoadLayer:public Layer
{
public :
	LoadLayer();
	~LoadLayer();
	virtual bool init() override;
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LoadLayer);
	void loadingCallback();
private:
	ProgressTimer *_timer;
	int _totalImage;
	int _loadImage;
	Label *_percentLabel;
	Label *_loadLabel;
	Sprite *_cloud;
};
#endif