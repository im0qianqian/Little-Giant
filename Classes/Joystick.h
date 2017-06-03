#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

class Joystick : public Node
{
public:
	Joystick();
	~Joystick();
	virtual bool init();
	CREATE_FUNC(Joystick);
	
	/* GET */
	bool getKeyW() const { return keyW; }
	bool getKeyA() const { return keyA; }
	bool getKeyS() const { return keyS; }
	bool getKeyD() const { return keyD; }

	/* 碰撞事件 */
	std::function<void(const Physics3DCollisionInfo &ci)> onPhysics3DCollision();

	/* 暂定、创建光效 */
	void createParticle(const Vec3 &pos);
private:
	/* 键盘监听 */
	void keyboardListen();
	/* 触屏监听 */
	void touchListen();

	/* 设置当前键盘按键状态 */
	void setKeyState(const EventKeyboard::KeyCode &keyCode, const bool &state);
	/* 鼠标三种事件 */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

	/* 一些按键 */
	bool keyW;
	bool keyA;
	bool keyS;
	bool keyD;
	EventListenerTouchAllAtOnce* _listenerTouch;	//触控监听器
	EventListenerKeyboard* _listenerKeyboard;	//键盘监听器
};

#endif