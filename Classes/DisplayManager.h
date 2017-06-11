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
	/* ��Ϸ���� ��ʾ���ֱ� */
	void showSorceBoard();
private:
	virtual void update(float dt) override;
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
	void applyToSkill(char skillName);
	Node *_displayNode;					// CSB node
	Text *_levelLabel;					// �ȼ�
	LoadingBar *_experienceBar;			// ������
	Button *_exitButton;				// �˳���ť
	Layout *_sorceBoard;				// �Ʒֱ�
	int _levelNum;						// ��ǰ�ȼ�
	float _percent;						// ��ǰ��������ռ�ٷֱ�
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
		/* ������ɫ */
		void setColor(const Color3B &color);
	private:   
		Text *_rank;
		Text *_name;
		Text *_sorce;
	};
	const int _scoreListSize = 6;
	std::vector<ListViewSorce> _scoreList;	//�ɼ�
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