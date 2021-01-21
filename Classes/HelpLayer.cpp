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
		// 加载 csb 文件
		_HelpNode = CSLoader::createNode("res/HelpLayer.csb");
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
