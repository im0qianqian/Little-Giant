#include "MainLayer.h"
#include "Global.h"
#include "GameScene.h"
#include "SceneManager.h"
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
		for (auto i = 0; i < 5; i++)
		{
			_button[i] = static_cast<Button*>(_displayNode->getChildByName("Button_" + to_string(i)));
			_button[i]->addClickEventListener(CC_CALLBACK_1(MainLayer::buttonCallBack , this));
		}
		addChild(_displayNode);
		flag = true;
	} while (false);
	cout << flag << endl;
	return flag;
}

void MainLayer::buttonCallBack(Ref * const node)
{
	int choose = static_cast<Node*>(node)->getTag();
	switch (choose)
	{
	case 0:
		GameScene::setGameMode(kGameModeAdventure);
		SceneManager::getInstance()->changeScene(kLoadingScene);
		break;
	case 1:
		GameScene::setGameMode(kGameModeTimer);
		SceneManager::getInstance()->changeScene(kLoadingScene);
		break;
	case 2:
		GameScene::setGameMode(kGameModeNight);
		SceneManager::getInstance()->changeScene(kLoadingScene);
		break;
	case 3:
		SceneManager::getInstance()->changeScene(kHelpScene);
		break;
	case 4:
		exit(0);
		break;
	default:
		break;
	}
	
}
