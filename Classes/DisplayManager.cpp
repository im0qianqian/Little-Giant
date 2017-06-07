#include "DisplayManager.h"
#include "Global.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui\UIListView.h"

DisplayManager::DisplayManager():
	_displayNode(nullptr),
	_levelLabel(nullptr),
	_experienceBar(nullptr)
{
	_sorceList.clear();
}

DisplayManager::~DisplayManager()
{
}

bool DisplayManager::init()
{
	bool flag = false;
	do
	{
		// 加载 csb 文件
		_displayNode = CSLoader::createNode("res/DisplayLayer.csb");
		// 获取其中的文本标签
		_levelLabel = static_cast<Text*>(_displayNode->getChildByName("Level_Label"));
		// 获取其中的进度条
		_experienceBar = static_cast<LoadingBar*>(_displayNode->getChildByName("Experience_bar"));
		// 获取成绩列表
		auto sorceList = static_cast<ListView*>(_displayNode->getChildByName("SorceListView"));
		for (auto i = 0; i < _sorceListSize; i++)
		{
			auto list = static_cast<ListView*>(sorceList->getChildByName("SorceList_" + to_string(i)));
			CCASSERT(list, "NULL");
			Text *rank = static_cast<Text*>(list->getChildByName("SorceList_rank"));
			Text *name = static_cast<Text*>(list->getChildByName("SorceList_name"));
			Text *sorce = static_cast<Text*>(list->getChildByName("SorceList_sorce"));
			CCASSERT(rank, "NULL");
			CCASSERT(name, "NULL");
			CCASSERT(sorce, "NULL");
			_sorceList.push_back(ListViewSorce(rank,name,sorce));
		}
		addChild(_displayNode);
		// 启动定时器开始更新
		schedule(schedule_selector(DisplayManager::update), .5f);
		flag = true;
	} while (0);
	return flag;
}

void DisplayManager::update(float dt)
{
	// 更新经验值
	updateExperience();
	// 更新成绩列表
	updateSorceList();
}

void DisplayManager::updateSorceList()
{
	if (_sorceList.size() < _sorceListSize)return;
	_sorceList[0].setName("qianqian");
	_sorceList[0].setRank("#1");
	_sorceList[0].setSorce(to_string(GameScene::getCharacterManager()->getPlayerCharacter()->getSorce()));
	if (GameScene::getCharacterManager()->getEnemyCharacter().size() < _sorceListSize - 1)return;
	for (auto i = 1; i < _sorceListSize; i++)
	{

	}
}

void DisplayManager::updateExperience()
{
	int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience();
	_levelLabel->setString(to_string(exp));
}

DisplayManager::ListViewSorce::ListViewSorce():
	_rank(nullptr),
	_name(nullptr),
	_sorce(nullptr)
{
}

DisplayManager::ListViewSorce::~ListViewSorce()
{
}

DisplayManager::ListViewSorce::ListViewSorce(Text * const & rank, Text * const & name, Text * const & sorce):
	_rank(rank),
	_name(name),
	_sorce(sorce)
{

}