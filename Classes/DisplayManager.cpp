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
		// ���� csb �ļ�
		_displayNode = CSLoader::createNode("res/DisplayLayer.csb");
		// ��ȡ���е��ı���ǩ
		_levelLabel = static_cast<Text*>(_displayNode->getChildByName("Level_Label"));
		// ��ȡ���еĽ�����
		_experienceBar = static_cast<LoadingBar*>(_displayNode->getChildByName("Experience_bar"));
		// ��ȡ�ɼ��б�
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
		// ������ʱ����ʼ����
		schedule(schedule_selector(DisplayManager::update), .02f);
		schedule(schedule_selector(DisplayManager::updateAnimation), .02f);
		flag = true;
	} while (0);
	return flag;
}

void DisplayManager::update(float dt)
{
	// ���¾���ֵ
	updateExperience();
	// ���³ɼ��б�
	updateSorceList();
}

void DisplayManager::updateAnimation(float dt)
{
	float nExp = _experienceBar->getPercent();
	if (nExp > int(_experience))
	{
		_experienceBar->setPercent(nExp - 1);
	}
	else if(nExp < int(_experience))
	{
		_experienceBar->setPercent(nExp + 1);
	}
}


void DisplayManager::updateSorceList()
{
	// ���ó��ϵ����е���set�����һ��vector
	vector<Character*> allCharacter(GameScene::getCharacterManager()->getEnemyCharacter().begin(), GameScene::getCharacterManager()->getEnemyCharacter().end());
	// ������ұ���
	allCharacter.push_back(GameScene::getCharacterManager()->getPlayerCharacter());
	// ��������
	sort(allCharacter.begin(), allCharacter.end(), [](Character * const &a, Character * const &b)
	{
		return a->getSorce()>b->getSorce();
	});
	CCASSERT(_scoreList.size() >= _scoreListSize, "�б�̫С");
	// ��ȡ��ǰ��������
	int size = allCharacter.size();
	int i;
	for (i = 0; i < size && i < _scoreListSize - 1; i++)	// i С����������С��5
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
	if (myrank < _scoreListSize)	//����ҵ�������ǰ������������ʾ
	{
		_scoreList[myrank+1].setColor(Color3B::YELLOW);	//������ɫ
	}
	_scoreList[0].setName("qianqian");
	_scoreList[0].setRank("#" + to_string(myrank+1));
	_scoreList[0].setSorce(to_string(myCharacter->getSorce()));
}

void DisplayManager::updateExperience()
{
	int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - (_levelnum+1)*(_levelnum+1)*(_levelnum+1);
	int _levelexperinence = (_levelnum + 2)*(_levelnum + 2)*(_levelnum+2) - (_levelnum +1)*(_levelnum +1)*(_levelnum +1);
	/*int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - (_levelnum + 1-1) * 5;
	int _levelexperinence = (_levelnum + 1 ) * 5 - (_levelnum + 1-1) * 5;*/
	//int _levelexperinence = 30 * ((_levelnum + 1)*(_levelnum + 1)*(_levelnum + 1) + 5 * (_levelnum + 1)) - 80 -30 * (_levelnum*_levelnum*_levelnum + 5 * _levelnum) - 80;
	if (exp >= _levelexperinence)
	{
		//_experienceBar->setPercent(100.f);
		_experience = 100.f;
		exp = exp - _levelexperinence;
		_levelnum++;
	}
	float _percent = (float)(exp) / (float)(_levelexperinence);
	//_experienceBar->setPercent(_percent*100);
	_experience = _percent * 100;
	CCLOG("***************%d %d %f", exp, _levelexperinence, _percent, _experience);
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
