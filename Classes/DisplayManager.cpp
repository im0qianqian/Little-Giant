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
	_promptLabel(nullptr),
	_currentTime(nullptr),
	_scoreList(std::vector<ListViewSorce>()),
	_levelNum(0),
	_percent(0)
{
	cout << "DisplayManager 构造" << endl;
}

DisplayManager::~DisplayManager()
{
	cout << "DisplayManager 析构" << endl;
}

bool DisplayManager::init()
{
	bool flag = false;
	do
	{
		// 加载 csb 文件
		_displayNode = CSLoader::createNode("res/DisplayLayer.csb");
		// 获取提示技能加成文本标签
		_promptLabel = static_cast<Text*>(_displayNode->getChildByName("Prompt_Label"));
		// 获取其中的文本标签
		_levelLabel = static_cast<Text*>(_displayNode->getChildByName("Level_Label"));
		// 获取剩余时间文本标签
		_currentTime = static_cast<Text*>(_displayNode->getChildByName("Current_Time"));
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
		// 获取技能面板
		for (int i = 0; i < 3; i++)
		{
			_skill_list[i] = static_cast<ListView*>(_displayNode->getChildByName("skill_list_" + to_string(i)));
			_skill_panel[i] = static_cast<PageView*>(_displayNode->getChildByName("skill_panel_" + to_string(i)));
		}
		// 获取退出按钮
		_exitButton = static_cast<Button*>(_displayNode->getChildByName("button_exit"));
		_exitButton->addClickEventListener([](Ref *const ref)
		{
			SceneManager::getInstance()->changeScene(kMenuScene);
		});
		// 获取计分表
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
		/* */
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
	if (GameScene::getGameMode() == kGameModeTimer)
	{
		// 更新剩余时间
		updateCurrentTime();
	}
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
	// 利用场上的所有敌人set构造出一个vector
	vector<Character*> allCharacter(GameScene::getCharacterManager()->getEnemyCharacter().begin(), GameScene::getCharacterManager()->getEnemyCharacter().end());
	auto myCharacter = GameScene::getCharacterManager()->getPlayerCharacter();
	// 加入玩家本身
	allCharacter.push_back(myCharacter);
	// 对其排序
	sort(allCharacter.begin(), allCharacter.end(), [](Character * const &a, Character * const &b)
	{
		return a->getSorce() > b->getSorce();
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
	auto myRank = find(allCharacter.begin(), allCharacter.end(), myCharacter) - allCharacter.begin();
	if (myRank < _scoreListSize - 1)	//如果我的排名在前五名，高亮显示
	{
		_scoreList[myRank + 1].setColor(Color3B::YELLOW);	//设置颜色
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
		_levelNum++;					// 等级++
		showSkillBoard();				// 显示升级技能选择
	}
	_percent = (float)(exp) / (float)(levelExperinence) * 100;
	//CCLOG("***************%d %d %f", exp, levelExperinence, _percent);
	_levelLabel->setString(to_string(_levelNum));
}

void DisplayManager::updateCurrentTime()
{
	int remainingTime = 25 - (GetCurrentTime() - GameScene::getStartingTime()) / 1000;
	if (remainingTime >= 0)
	{
		_currentTime->setString(u8"时间剩余 " + to_string(remainingTime) + "s");
	}
	else
	{
		// 停止所有定时器
		unscheduleAllSelectors();
		// 显示得分面板
		showSorceBoard();
	}
}

void DisplayManager::showSorceBoard()
{
	_sorceBoard->setVisible(true);
	_sorceNum->setString(to_string(GameScene::getCharacterManager()->getPlayerCharacter()->getSorce()));
}

void DisplayManager::showSkillBoard()
{
	int ratio = rand() % 17;
	CCLOG("%d", ratio);
	if (ratio % 2 == 1)
		ratio--;
	CCLOG("%d", ratio);
	for (int i = 0; i < 3; i++)
	{
		_skill_list[i]->setVisible(true);
		_skill_list[i]->setScrollBarOpacity(0);
		_skill_panel[i]->setVisible(true);
	}
	for (int i = 0; i < 3; i++)
	{
		_skill_list[i]->jumpToPercentVertical((ratio / 16.0)*100.0);
		_skill_list[i]->setDirection(ScrollView::Direction::NONE);
		int skillNum = _skill_list[i]->getItems().size();
		for (size_t j = 0; j < skillNum; j++)
		{
			Widget* item = _skill_list[i]->getItem(j);//获取其中的某个项，然后转换成Button 进行设置操作=
			item->addClickEventListener([this](Ref *const ref)
			{
				// 先隐藏三个技能面板
				for (int i = 0; i < 3; i++)
				{
					_skill_list[i]->setVisible(false);
					_skill_panel[i]->setVisible(false);
				}
				// 获取技能标签
				int itemTag = static_cast<Node*>(ref)->getTag();
				// 应用技能
				applyToSkill(itemTag);
			});
		}
	}
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

void DisplayManager::applyToSkill(const int &skillTag)
{
	auto character = GameScene::getCharacterManager()->getPlayerCharacter();
	string prompt;
	switch (skillTag)
	{
	case 0:
		character->getAttribute().addAttackDamage(.1f);
		prompt = u8"攻击力提升";
		break;
	case 1:
		character->getAttribute().addAttackSpeed(.1f);
		prompt = u8"攻击速度提升";
		break;
	case 2:
		character->getAttribute().addAttackSpeed(.1f);
		prompt = u8"攻击速度提升";
		break;
	case 3:
		character->getAttribute().addDefensiveForce(5.f);
		prompt = u8"防御力提升";
		break;
	case 4:
		character->getAttribute().addAttackDamage(.1f);
		prompt = u8"攻击力提升";
		break;
	case 5:
		character->getAttribute().addDefensiveForce(5.f);
		prompt = u8"防御力提升";
		break;
	case 6:
		character->getAttribute().addRestoringAbility(.1f);
		prompt = u8"恢复能力提升";
		break;
	case 7:
		character->getAttribute().addMovingSpeed(3.f);
		prompt = u8"移动速度提升";
		break;
	case 8:
		character->getAttribute().addEmpiricalAcquisition(.5f);
		prompt = u8"经验获取能力提升";
		break;
	default:
		break;
	}
	_promptLabel->setString(prompt);
	_promptLabel->setOpacity(0);
	_promptLabel->runAction(Sequence::create(CCFadeIn::create(1.f), CCDelayTime::create(.5f), CCFadeOut::create(1.f), nullptr));
}