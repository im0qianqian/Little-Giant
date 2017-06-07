#include "DisplayManager.h"
#include "Global.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui\UIListView.h"
#include <vector>
#include <algorithm>
DisplayManager::DisplayManager():
	_displayNode(nullptr),
	_levelLabel(nullptr),
	_experienceBar(nullptr)
{
	_scoreList.clear();
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
		for (auto i = 0; i < _scoreListSize; i++)
		{
			auto list = static_cast<ListView*>(sorceList->getChildByName("SorceList_" + to_string(i)));
			CCASSERT(list, "NULL");
			Text *rank = static_cast<Text*>(list->getChildByName("SorceList_rank"));
			Text *name = static_cast<Text*>(list->getChildByName("SorceList_name"));
			Text *sorce = static_cast<Text*>(list->getChildByName("SorceList_sorce"));
			CCASSERT(rank, "NULL");
			CCASSERT(name, "NULL");
			CCASSERT(sorce, "NULL");
			_scoreList.push_back(ListViewSorce(rank, name, sorce));
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
	if (_scoreList.size() < _scoreListSize)return;
	auto person = GameScene::getCharacterManager()->getAllCharacter();
	std::sort(person.begin(), person.end(), [](Character * const &a, Character * const &b)
	{
		return a->getSorce()>b->getSorce();
	}
	);
	_scoreList[0].setName("qianqian");
	_scoreList[0].setRank("#1");
	_scoreList[0].setSorce(to_string(GameScene::getCharacterManager()->getPlayerCharacter()->getSorce()));
	int size = person.size();
	for (auto i = 0; i < _scoreListSize-1; i++)
	{
		_scoreList[i+1].setRank(to_string(i+1));
		_scoreList[i+1].setName(person[i]->getName());
		_scoreList[i+1].setSorce(to_string(person[i]->getSorce()));
		if (i>=size)break;
	}
}

void DisplayManager::updateExperience()
{
	int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - (_levelnum + 1-1) * 5;
	int _levelexperinence = (_levelnum + 1 ) * 5 - (_levelnum + 1-1) * 5;
	//int _levelexperinence = 30 * ((_levelnum + 1)*(_levelnum + 1)*(_levelnum + 1) + 5 * (_levelnum + 1)) - 80 -30 * (_levelnum*_levelnum*_levelnum + 5 * _levelnum) - 80;
	if (exp >= _levelexperinence)
	{
		_experienceBar->setPercent(100.f);
		exp = exp - _levelexperinence;
		_levelnum++;
	}
	float _percent = (float)(exp) / (float)(_levelexperinence);
	CCLOG("***************%d %d %f", exp, _levelexperinence, _percent);
	_experienceBar->setPercent(_percent*100);
	_levelLabel->setString(to_string(_levelnum));
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