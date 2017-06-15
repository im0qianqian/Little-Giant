#include "HelpLayer.h"
#include "Global.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"

HelpLayer::HelpLayer()
{
}

HelpLayer::~HelpLayer()
{
}

bool HelpLayer::init()
{
	bool flag = false;
	do
	{
		// ╪сть csb нд╪Ч
		_HelpNode = CSLoader::createNode("res/HelpScene.csb");
		_button = static_cast<Button*>(_HelpNode->getChildByName("Button_0"));
		_button->addClickEventListener(CC_CALLBACK_1(HelpLayer::buttonCallBack, this));
		addChild(_HelpNode);
		flag = true;
	} while (false);
	cout << flag << endl;
	return flag;
}

void HelpLayer::buttonCallBack(Ref * const node)
{
	SceneManager::getInstance()->changeScene(kMenuScene);
}
