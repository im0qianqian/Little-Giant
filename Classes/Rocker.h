#ifndef __ROCKER_H__
#define __ROCKER_H__

#include "cocos2d.h"
USING_NS_CC;

class Rocker : public Node
{
public:
	static Rocker* create(const std::string &rockerImageName, const std::string &rockerBGImageName, const Vec2 &pos);
	//ҡ�˵�ǰ��ָ��������
	Vec2 getDirection() const;
private:
	typedef enum {
		tag_rocker,
		tag_rockerBG,
	}tagForHRocker;
	CREATE_FUNC(Rocker);
	void rockerInit(const std::string &rockerImageName, const std::string &rockerBGImageName, const Vec2 &pos);
	//�õ��뾶Ϊr��Բ���˶���һ���Ƕ�Ӧ��Ӧ��x,y����  
	Vec2 getAnglePosition(const float &r, const float &angle);
	//�����¼�  
	virtual bool onTouchBegan(Touch* const &touch, Event* const &event);
	virtual void onTouchMoved(Touch* const &touch, Event* const &event);
	virtual void onTouchEnded(Touch* const &touch, Event* const &event);
	//�õ�ҡ�����û�������ĽǶ�  
	float getRad(const Vec2 &pos1, const Vec2 &pos2);
	//ҡ�˱���������  
	Vec2 _rockerBGPosition;
	//ҡ�˱����İ뾶
	float _rockerBGR;
	//�Ƿ�ɲ���ҡ��
	bool _isCanMove;
	//������
	EventListenerTouchOneByOne* _listener;
};
#endif