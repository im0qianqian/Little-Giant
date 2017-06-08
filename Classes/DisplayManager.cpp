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
	_experienceBar(nullptr),
	_levelnum(0),
	_experience(0)
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
		schedule(schedule_selector(DisplayManager::updateAnimation), .02f);
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

void DisplayManager::updateAnimation(float dt)
{
	float nExp = _experienceBar->getPercent();
	if (nExp > _percent)
	{
		_experienceBar->setPercent(nExp - 1);
	}
	else if (nExp < _percent)
	{
		_experienceBar->setPercent(nExp + 1);
	}
}


void DisplayManager::updateSorceList()
{
	// 利用场上的所有敌人set构造出一个vector
	vector<Character*> allCharacter(GameScene::getCharacterManager()->getEnemyCharacter().begin(), GameScene::getCharacterManager()->getEnemyCharacter().end());
	// 加入玩家本身
	allCharacter.push_back(GameScene::getCharacterManager()->getPlayerCharacter());
	// 对其排序
	sort(allCharacter.begin(), allCharacter.end(), [](Character * const &a, Character * const &b)
	{
		return a->getSorce()>b->getSorce();
	});
	CCASSERT(_scoreList.size() >= _scoreListSize, "列表太小");
	// 获取当前场上人数
	int size = allCharacter.size();
	int i;
	for (i = 0; i < size && i < _scoreListSize - 1; i++)	// i 小于人数并且小于5
	{
		_scoreList[i + 1].setName(allCharacter[i]->getName());
		_scoreList[i + 1].setRank("#" + to_string(i + 1));
		_scoreList[i + 1].setSorce(to_string(allCharacter[i]->getSorce()));
		_scoreList[i + 1].setColor(Color3B::WHITE);
	}
	for (; i < _scoreListSize - 1; i++)
	{
		_scoreList[i + 1].setName("");
		_scoreList[i + 1].setRank("");
		_scoreList[i + 1].setSorce("");
	}
	auto myCharacter = GameScene::getCharacterManager()->getPlayerCharacter();
	auto myrank = find(allCharacter.begin(), allCharacter.end(), myCharacter)-allCharacter.begin();
	if (myrank < _scoreListSize)	//如果我的排名在前五名，高亮显示
	{
		_scoreList[myrank+1].setColor(Color3B::YELLOW);	//设置颜色
	}
	_scoreList[0].setName("qianqian");
	_scoreList[0].setRank("#" + to_string(myrank+1));
	_scoreList[0].setSorce(to_string(myCharacter->getSorce()));
}

void DisplayManager::updateExperience()
{
	int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - getLevelExperience(_levelnum);
	int levelExperinence = getLevelExperience(_levelnum + 1) - getLevelExperience(_levelnum);
	/*int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - (_levelnum)*(_levelnum)*(_levelnum);
	int levelExperinence = (_levelnum + 1)*(_levelnum + 1)*(_levelnum+1) - (_levelnum )*(_levelnum )*(_levelnum );*/
	if (exp >= levelExperinence)
	{
		exp = exp - levelExperinence;
		_levelnum++;
	}
	_percent = (float)(exp) / (float)(levelExperinence)*100;
	CCLOG("***************%d %d %f", exp, levelExperinence, _percent);
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

void DisplayManager::ListViewSorce::setColor(const Color3B &color)
{
	_rank->setColor(color);
	_name->setColor(color);
	_sorce->setColor(color);
}
