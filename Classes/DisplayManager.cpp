#include "DisplayManager.h"
#include "Global.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "ui\UIListView.h"
#include "ui\UIScrollView.h"
#include <vector>
#include <algorithm>
DisplayManager::DisplayManager() :
	_displayNode(nullptr),
	_levelLabel(nullptr),
	_experienceBar(nullptr),
	_exitButton(nullptr),
	_sorceBoard(nullptr),
	_levelNum(0),
	_percent(0)
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
		skill_list_0 = static_cast<ListView*>(_displayNode->getChildByName("skill_list_0"));
		skill_list_1 = static_cast<ListView*>(_displayNode->getChildByName("skill_list_1"));
		skill_list_2 = static_cast<ListView*>(_displayNode->getChildByName("skill_list_2"));
		skill_panel_0 = static_cast<Label*>(_displayNode->getChildByName("skill_panel_0"));
		skill_panel_1 = static_cast<Label*>(_displayNode->getChildByName("skill_panel_1"));
		skill_panel_2 = static_cast<Label*>(_displayNode->getChildByName("skill_panel_2"));
		skill_list_0->setVisible(false);
		skill_list_1->setVisible(false);
		skill_list_2->setVisible(false);
		skill_panel_0->setVisible(false);
		skill_panel_1->setVisible(false);
		skill_panel_2->setVisible(false);
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
		// ��ȡ�˳���ť
		_exitButton = static_cast<Button*>(_displayNode->getChildByName("button_exit"));
		// ��ȡ�Ʒֱ�
		_sorceBoard = static_cast<Layout*>(_displayNode->getChildByName("SorceBoard"));
		/* �����ݶ����� */
		_exitButton->setVisible(false);
		_sorceBoard->setVisible(false);
		/* */
		addChild(_displayNode);
		// ������ʱ����ʼ����
		schedule(schedule_selector(DisplayManager::update), .5f);
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
	if (nExp > int(_percent))
	{
		_experienceBar->setPercent(nExp - 1);
	}
	else if (nExp < int(_percent))
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
		return a->getSorce() > b->getSorce();
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
	auto myrank = find(allCharacter.begin(), allCharacter.end(), myCharacter) - allCharacter.begin();
	if (myrank < _scoreListSize)	//����ҵ�������ǰ������������ʾ
	{
		_scoreList[myrank + 1].setColor(Color3B::YELLOW);	//������ɫ
	}
	_scoreList[0].setName("qianqian");
	_scoreList[0].setRank("#" + to_string(myrank + 1));
	_scoreList[0].setSorce(to_string(myCharacter->getSorce()));
}

void DisplayManager::updateExperience()
{
	int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - getLevelExperience(_levelNum);
	int levelExperinence = getLevelExperience(_levelNum + 1) - getLevelExperience(_levelNum);
	/*int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - (_levelnum)*(_levelnum)*(_levelnum);
	int levelExperinence = (_levelnum + 1)*(_levelnum + 1)*(_levelnum+1) - (_levelnum )*(_levelnum )*(_levelnum );*/
	if (exp >= levelExperinence)
	{
		exp = exp - levelExperinence;
		_levelNum++;
		skill_list_0->setVisible(true); 
		skill_list_1->setVisible(true);
		skill_list_2->setVisible(true);
		skill_panel_0->setVisible(true);
		skill_panel_1->setVisible(true);
		skill_panel_2->setVisible(true);
		/*skill_list_0->setInertiaScrollEnabled(true);
		skill_list_1->setInertiaScrollEnabled(true);
		skill_list_2->setInertiaScrollEnabled(true);*/
		skill_list_0->setScrollBarOpacity(0);
		skill_list_1->setScrollBarOpacity(0);
		skill_list_2->setScrollBarOpacity(0);
		skill_list_0->scrollToTop(1, true);
		skill_list_0->cocos2d::ui::ListView::addClickEventListener(CC_CALLBACK_1(DisplayManager::ListViewMoveCallback, this));
	}
	_percent = (float)(exp) / (float)(levelExperinence) * 100;
	CCLOG("***************%d %d %f", exp, levelExperinence, _percent);
	_levelLabel->setString(to_string(_levelNum));
}

void DisplayManager::showSorceBoard()
{
	_sorceBoard->setVisible(true);
}

void DisplayManager::showSkillBoard()
{
}

DisplayManager::ListViewSorce::ListViewSorce() :
	_rank(nullptr),
	_name(nullptr),
	_sorce(nullptr)
{
}

DisplayManager::ListViewSorce::~ListViewSorce()
{
}

DisplayManager::ListViewSorce::ListViewSorce(Text * const & rank, Text * const & name, Text * const & sorce) :
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

void DisplayManager::ListViewMoveCallback(cocos2d::Ref *pSender)
{
	skill_list_0->setVisible(false);
	skill_list_1->setVisible(false);
	skill_list_2->setVisible(false);
	skill_panel_0->setVisible(false);
	skill_panel_1->setVisible(false);
	skill_panel_2->setVisible(false);/*
	auto skill_list = static_cast<Text *>(pSender);
	CCLOG("click btn Tag=%s", skill_list->getTag());*/
}
