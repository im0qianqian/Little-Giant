#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"
#include "Global.h"
#include "ui\UIText.h"
#include "ui\UILoadingBar.h"
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
	virtual bool init();
	CREATE_FUNC(DisplayManager);
	/* ��Ϸ���� ��ʾ���ֱ� */
	void showSorceBoard();
private:
	void update(float dt);
	/* ���¶���Ч�� */
	void updateAnimation(float dt);
	/* �������а� */
	void updateSorceList();
	/* ���¾����� */
	void updateExperience();
	/* ��ȡ��ǰ�ȼ���������Ҫ�ľ���� */
	int getLevelExperience(int const &levelNum){ return levelNum*levelNum*levelNum+6*levelNum; }
	/* �������� ��ʾ����ѡ���� */
	void showSkillBoard();
	void ListViewMoveCallback(cocos2d::Ref *pSender);
	Node *_displayNode;					// CSB node
	Text *_levelLabel;					// �ȼ�
	LoadingBar *_experienceBar;			// ������
	Button *_exitButton;				// �˳���ť
	Layout *_sorceBoard;				// �Ʒֱ�
	int _levelNum;						// ��ǰ�ȼ�
	float _percent;						// ��ǰ��������ռ�ٷֱ�
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
		/* ������ɫ */
		void setColor(const Color3B &color);
	private:
		Text *_rank;
		Text *_name;
		Text *_sorce;
	};
	const int _scoreListSize = 6;
	std::vector<ListViewSorce> _scoreList;	//�ɼ�
};

#endif