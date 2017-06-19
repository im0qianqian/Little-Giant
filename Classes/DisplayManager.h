#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

#include "cocos2d.h"
#include "Global.h"
#include "ui\UIText.h"
#include "ui\UILoadingBar.h"
#include "Character.h"
#include "Rocker.h"
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
	/* ��ȡ�����˶���ָ�� */
	Rocker *getRocker() const{ return _rocker; }
private:
	virtual void update(float dt) override;
	/* ���¶���Ч�� */
	void updateAnimation(float dt);
	/* �������а� */
	void updateSorceList();
	/* ���¾����� */
	void updateExperience();
	/* ����ʣ��ʱ�� */
	void updateCurrentTime();
	/* ��ȡ��ǰ�ȼ���������Ҫ�ľ���� */
	int getLevelExperience(int const &levelNum){ return levelNum*levelNum*levelNum+6*levelNum; }
	/* �������� ��ʾ����ѡ���� */
	void showSkillBoard();
	/* ���＼��Ӧ�� */
	void applyToSkill(const int &skillTag);

	Node *_displayNode;					// CSB node
	Text *_levelLabel;					// �ȼ�
	Text *_promptLabel;                 // ��ʾ���ܼӳ�����
	Text *_currentTime;					// ��ǰʱ��
	LoadingBar *_experienceBar;			// ������
	Button *_exitButton;				// �˳���ť
	Button *_buttonHome;				//Home
	Button *_buttonRestart;
	Layout *_sorceBoard;				// �Ʒֱ�
	Text *_sorceNum;					// ���յ÷�
	Text *_sorceRank;					// ��������
	int _levelNum;						// ��ǰ�ȼ�
	float _percent;						// ��ǰ��������ռ�ٷֱ�
	ListView* _skill_list[3];
	PageView* _skill_panel[3];
	Rocker *_rocker;					//������
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