#ifndef __ROCKER_H__
#define __ROCKER_H__

#include "cocos2d.h"
USING_NS_CC;

class Rocker : public Node
{
public:
	static Rocker* create(const std::string &rockerImageName, const std::string &rockerBGImageName, const Vec2 &pos);
	//摇杆当前所指方向向量
	Vec2 getDirection() const;
private:
	typedef enum {
		tag_rocker,
		tag_rockerBG,
	}tagForHRocker;
	CREATE_FUNC(Rocker);
	void rockerInit(const std::string &rockerImageName, const std::string &rockerBGImageName, const Vec2 &pos);
	//得到半径为r的圆周运动上一个角度应对应的x,y坐标  
	Vec2 getAnglePosition(const float &r, const float &angle);
	//触屏事件  
	virtual bool onTouchBegan(Touch* const &touch, Event* const &event);
	virtual void onTouchMoved(Touch* const &touch, Event* const &event);
	virtual void onTouchEnded(Touch* const &touch, Event* const &event);
	//得到摇杆与用户触屏点的角度  
	float getRad(const Vec2 &pos1, const Vec2 &pos2);
	//摇杆背景的坐标  
	Vec2 _rockerBGPosition;
	//摇杆背景的半径
	float _rockerBGR;
	//是否可操作摇杆
	bool _isCanMove;
	//监听器
	EventListenerTouchOneByOne* _listener;
};
#endif