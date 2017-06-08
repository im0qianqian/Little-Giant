#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"
#include "Global.h"
#include "ui\UIText.h"
#include "ui\UILoadingBar.h"
#include "ui\UIListView.h"

USING_NS_CC;
using namespace cocos2d::ui;

class DisplayManager :public Layer
{
public:
	DisplayManager();
	~DisplayManager();
	virtual bool init();
	CREATE_FUNC(DisplayManager);
private:
	void update(float dt);
	void updateAnimation(float dt);
	void updateSorceList();
	void updateExperience();
	int getLevelExperience(int const &levelNum){ return levelNum*levelNum*levelNum+6*levelNum; }
	void ListViewMoveCallback(cocos2d::Ref *pSender);
	Node *_displayNode;					// CSB node
	Text *_levelLabel;					// 等级
	LoadingBar *_experienceBar;			// 经验条
	int _levelNum;
	float _percent;                    //当前经验条所占百分比
	ListView* skill_list_0;
	ListView* skill_list_1;
	ListView* skill_list_2;
	Label* skill_panel_0;
	Label* skill_panel_1;
	Label* skill_panel_2;
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
};

#endif