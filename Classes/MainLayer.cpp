#include "MainLayer.h"
#include "Global.h"
#include "cocostudio/CocoStudio.h"

MainLayer::MainLayer()
{
}

MainLayer::~MainLayer()
{
}

bool MainLayer::init()
{
	bool flag = false;
	do
	{
		// ╪сть csb нд╪Ч
		_displayNode = CSLoader::createNode("res/MainLayer.csb");
		for (auto i = 0; i < 3; i++)
		{
			_button[i] = static_cast<Button*>(_displayNode->getChildByName("Button_" + to_string(i)));
		}
		addChild(_displayNode);
		flag = true;
	} while (false);
	return flag;
}
