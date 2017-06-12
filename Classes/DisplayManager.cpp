#include "DisplayManager.h"
#include "Global.h"
#include "GameScene.h"
#include "Character.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "ui\UIPageView.h"
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
	_sorceNum(nullptr),
	_buttonHome(nullptr),
	_buttonRestart(nullptr),
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
		//��ȡ��ʾ���ܼӳ��ı���ǩ
		_promptLabel = static_cast<Text*>(_displayNode->getChildByName("Prompt_Label"));
		// ��ȡ���е��ı���ǩ
		_levelLabel = static_cast<Text*>(_displayNode->getChildByName("Level_Label"));
		// ��ȡ���еĽ�����
		_experienceBar = static_cast<LoadingBar*>(_displayNode->getChildByName("Experience_bar"));
		// ��ȡ�ɼ��б�
		auto sorceList = static_cast<ListView*>(_displayNode->getChildByName("SorceListView"));
		for (int i = 0; i < 3; i++)
		{
			/*string name = "skill_list_" + std::to_string(i);
			CCLOG("%s", name);*/
			skill_list[i] = static_cast<ListView*>(_displayNode->getChildByName(skill_ListName[i]));
			skill_panel[i] = static_cast<PageView*>(_displayNode->getChildByName(skill_PanelName[i]));
			skill_list[i]->setVisible(false);
			skill_panel[i]->setVisible(false);
		}
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
		_exitButton->addClickEventListener([](Ref *const ref)
		{
			SceneManager::getInstance()->changeScene(kMenuScene);
		});
		// ��ȡ�Ʒֱ�
		_sorceBoard = static_cast<Layout*>(_displayNode->getChildByName("SorceBoard"));
		_sorceNum = static_cast<Text*>(_sorceBoard->getChildByName("sorce_num"));
		_buttonHome = static_cast<Button*>(_sorceBoard->getChildByName("Button_home"));
		_buttonHome->addClickEventListener([](Ref *const ref)
		{
			SceneManager::getInstance()->changeScene(kMenuScene);
		});
		_buttonRestart = static_cast<Button*>(_sorceBoard->getChildByName("Button_restart"));
		_buttonRestart->addClickEventListener([](Ref *const ref)
		{
			SceneManager::getInstance()->changeScene(kGameScene);
		});
		/* �����ݶ����� */
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
	auto myCharacter = GameScene::getCharacterManager()->getPlayerCharacter();
	// ������ұ���
	allCharacter.push_back(myCharacter);
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
	auto myRank = find(allCharacter.begin(), allCharacter.end(), myCharacter) - allCharacter.begin();
	if (myRank < _scoreListSize - 1)	//����ҵ�������ǰ������������ʾ
	{
		_scoreList[myRank + 1].setColor(Color3B::YELLOW);	//������ɫ
	}
	_scoreList[0].setName(myCharacter->getName());
	_scoreList[0].setRank("#" + to_string(myRank + 1));
	_scoreList[0].setSorce(to_string(myCharacter->getSorce()));
}

void DisplayManager::updateExperience()
{
	if (GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() == 0)_levelNum = 0;
	int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - getLevelExperience(_levelNum);
	int levelExperinence = getLevelExperience(_levelNum + 1) - getLevelExperience(_levelNum);
	/*int exp = GameScene::getCharacterManager()->getPlayerCharacter()->getExperience() - (_levelnum)*(_levelnum)*(_levelnum);
	int levelExperinence = (_levelnum + 1)*(_levelnum + 1)*(_levelnum+1) - (_levelnum )*(_levelnum )*(_levelnum );*/
	if (exp >= levelExperinence)
	{
		exp = exp - levelExperinence;
		_levelNum++;
		int ratio = rand() % 17 ;
		CCLOG("%d", ratio);
		if (ratio % 2 == 1)
			ratio --;
		CCLOG("%d", ratio);
		for (int i = 0; i < 3; i++)
		{
			skill_list[i]->setVisible(true);
			skill_list[i]->setScrollBarOpacity(0);
			skill_panel[i]->setVisible(true);
			skill_list[i]->setDirection(ScrollView::Direction::VERTICAL);
			skill_list[i]->scrollToBottom(5.0, true);
			skill_list[i]->scrollToTop(5.0, true);
		}
		for (int i = 0; i < 3;i++)
		{
			skill_list[i]->scrollToBottom(5.0, true);
			skill_list[i]->scrollToTop(5.0, true);
			/*skill_list[i]->scrollToBottom(5.0, true);
			skill_list[i]->scrollToTop(5.0, true);*/
			skill_list[i]->jumpToPercentVertical((ratio / 16.0)*100.0);
			/*Widget* item = skill_list[i]->getCurrentFocusedWidget(true);*/
		   // skill_list[i]->setEnabled(false);
			//skill_list[i]->setPropagateTouchEvents(true);
			skill_list[i]->setDirection(ScrollView::Direction::NONE);
			//skill_list[i]->setFocused(false);
			//skill_list[i]->setItemsMargin(5.0);
			//skill_list[i]->setClippingEnabled(true);
			//skill_list[i]->setFocusEnabled(false);
			/*
			skill_list[i]->getTopBoundary();
			skill_list[i]->getCurrentFocusedWidget(true);*/
			/*skill_list[i]->jumpToPercentVertical(0.25);*/

			//skill_panel[i]->addClickEventListener(CC_CALLBACK_1(DisplayManager::ListViewMoveCallback, this));
			int skillNum=skill_list[i]->getItems().size();
			for (size_t j = 0; j < skillNum; j++)
			{
				Widget* item = skill_list[i]->getItem(j);//��ȡ���е�ĳ���Ȼ��ת����Button �������ò���
				/*Button* button = static_cast<Button*>(item->getChildByName("Title Button"));
				ssize_t index = skill_list[i]->getIndex(item);*/
				item->addClickEventListener(CC_CALLBACK_1(DisplayManager::ListViewMoveCallback, this));
			}

		}
	}
	_percent = (float)(exp) / (float)(levelExperinence) * 100;
	//CCLOG("***************%d %d %f", exp, levelExperinence, _percent);
	_levelLabel->setString(to_string(_levelNum));
}

void DisplayManager::showSorceBoard()
{
	_sorceBoard->setVisible(true);
	cout << GameScene::getCharacterManager()->getPlayerCharacter()->getSorce() << endl;
	cout << _sorceNum << endl;
	_sorceNum->setString(to_string(GameScene::getCharacterManager()->getPlayerCharacter()->getSorce()));
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
	for (int i = 0; i < 3; i++)
	{
		skill_list[i]->setVisible(false);
		skill_panel[i]->setVisible(false);
	}

	auto *touchItem = static_cast<Widget *>(pSender);
	int itemTag = touchItem->getTag();
	applyToSkill(itemTag);

}
void DisplayManager::applyToSkill(const int &skillTag)
{
	auto character = GameScene::getCharacterManager()->getPlayerCharacter();
	string prompt;
	switch (skillTag)
	{
	case 0:
		character->getAttribute().addAttackDamage(.1f);
		prompt = u8"����������";
		break;
	case 1:
		character->getAttribute().addAttackSpeed(.1f);
		prompt = u8"�����ٶ�����";
		break;
	case 2:
		character->getAttribute().addAttackSpeed(.1f);
		prompt = u8"�����ٶ�����";
		break;
	case 3:
		character->getAttribute().addDefensiveForce(5.f);
		prompt = u8"����������";
		break;
	case 4:
		character->getAttribute().addAttackDamage(.1f);
		prompt = u8"����������";
		break;
	case 5:
		character->getAttribute().addDefensiveForce(5.f);
		prompt = u8"����������";
		break;
	case 6:
		character->getAttribute().addRestoringAbility(.1f);
		prompt = u8"�ָ���������";
		break;
	case 7:
		character->getAttribute().addMovingSpeed(3.f);
		prompt = u8"�ƶ��ٶ�����";
		break;
	case 8:
		character->getAttribute().addEmpiricalAcquisition(.5f);
		prompt = u8"�����ȡ��������";
		break;
	default:
		break;
	}
	_promptLabel->setString(prompt);
	_promptLabel->setOpacity(0);
	_promptLabel->runAction(Sequence::create(CCFadeIn::create(1.f), CCDelayTime::create(.5f), CCFadeOut::create(1.f), nullptr));
}