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
	bool getKeyW() const { return _keyW; }
	bool getKeyA() const { return _keyA; }
	bool getKeyS() const { return _keyS; }
	bool getKeyD() const { return _keyD; }

	/* 碰撞事件 */
	std::function<void(const Physics3DCollisionInfo &ci)> onPhysics3DCollision();

	/* 暂定、创建光效 */
	void createParticle(const Vec3 &pos);

	/* 是否是第一人称视角 */
	bool isFirstView() { return _isFirstView; }
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
	bool _keyW;
	bool _keyA;
	bool _keyS;
	bool _keyD;
	bool _isFirstView;								//是否为第一人称视角
	EventListenerTouchAllAtOnce* _listenerTouch;	//触控监听器
	EventListenerKeyboard* _listenerKeyboard;	//键盘监听器
};

#endif