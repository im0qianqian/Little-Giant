#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"
#include "ui\UIText.h"
#include "ui\UILoadingBar.h"

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
	void updateSorceList();
	void updateExperience();
	Node *_displayNode;				// CSB node
	Text *_levelLabel;					// 等级
	LoadingBar *_experienceBar;	// 经验条
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
	private:
		Text *_rank;
		Text *_name;
		Text *_sorce;
	};
	const int _sorceListSize = 6;
	std::vector<ListViewSorce> _sorceList;	//成绩
};

#endif