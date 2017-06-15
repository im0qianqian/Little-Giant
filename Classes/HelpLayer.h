#pragma once
#ifndef __HELP_LAYER_H__
#define __HELP_LAYER_H__

#include "cocos2d.h"
#include "ui\UIButton.h"
USING_NS_CC;
using namespace ui;

class HelpLayer :public Layer
{
public:
	HelpLayer();
	~HelpLayer();
	virtual bool init() override;
	CREATE_FUNC(HelpLayer);
	void buttonCallBack(Ref * const node);
private:
	Node *_HelpNode;	
	Button *_button;
};

#endif