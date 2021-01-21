#ifndef __MAIN_LAYER_H__
#define __MAIN_LAYER_H__

#include "cocos2d.h"
#include "ui\UIButton.h"
USING_NS_CC;
using namespace ui;

class MainLayer :public Layer
{
public:
	MainLayer();
	~MainLayer();
	virtual bool init() override;
	CREATE_FUNC(MainLayer);
	void buttonCallBack(Ref * const node);
private:
	Node *_displayNode;		//CSB文件
	Button *_button[5];		//按钮
};

#endif