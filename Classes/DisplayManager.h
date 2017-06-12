#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"
#include "Global.h"
#include "ui\UIText.h"
#include "ui\UILoadingBar.h"
#include "Character.h"
#include "ui\UIButton.h"
#include "ui\UILayout.h"
#include "ui\UIListView.h"

USING_NS_CC;
using namespace cocos2d::ui;

class DisplayManager :public Layer
{
public:
	DisplayManager();
	~DisplayManager();
	virtual bool init() override;
	CREATE_FUNC(DisplayManager);
	/* 游戏结束 显示积分表 */
	void showSorceBoard();
private:
	virtual void update(float dt) override;
	/* 更新动画效果 */
	void updateAnimation(float dt);
	/* 更新排行榜 */
	void updateSorceList();
	/* 更新经验条 */
	void updateExperience();
	/* 获取当前等级升级所需要的经验点 */
	int getLevelExperience(int const &levelNum){ return levelNum*levelNum*levelNum+6*levelNum; }
	/* 人物升级 显示技能选择栏 */
	void showSkillBoard();
	void ListViewMoveCallback(cocos2d::Ref *pSender);
	void applyToSkill(const int &skillTag);
	Node *_displayNode;					// CSB node
	Text *_levelLabel;					// 等级
	Text *_promptLabel;                 //提示技能加成种类
	LoadingBar *_experienceBar;			// 经验条
	Button *_exitButton;				// 退出按钮
	Button *_buttonHome;				//Home
	Button *_buttonRestart;
	Layout *_sorceBoard;				// 计分表
	Text *_sorceNum;					// 最终得分
	int _levelNum;						// 当前等级
	float _percent;						// 当前经验条所占百分比
	ListView* skill_list[3];
	PageView* skill_panel[3];
	class ListViewSorce
	{
	public:
		ListViewSorce();
		~ListViewSorce();
		ListViewSorce(Text *const &rank, Text *const &name, Text *const &sorce);
		/* GET */
		string getRank() const { return _rank->getString(); }
		string getName() const { return _name->getString(); }
		string getSorce() const { return _sorce->getString(); }
		/* SET */
		void setRank(string const &rank) { _rank->setString(rank); }
		void setName(string const &name) { _name->setString(name); }
		void setSorce(string const &sorce) { _sorce->setString(sorce); }
		/* 设置颜色 */
		void setColor(const Color3B &color);
	private:   
		Text *_rank;
		Text *_name;
		Text *_sorce;
	};
	const int _scoreListSize = 6;
	std::vector<ListViewSorce> _scoreList;	//成绩
	/*enum skillName
	{
		skill_0,
		skill_1,
		skill_2,
		skill_3,
		skill_4,
		skill_5,
		skill_6,
		skill_7
	};
	skillName skillname;*/
};

#endif