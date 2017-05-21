#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h"

USING_NS_CC;

class Joystick : public Layer
{
public:
	Joystick();
	~Joystick();
	virtual bool init();
	/* 设置当前键盘按键状态 */
	static void setKeyState(EventKeyboard::KeyCode keyCode, bool state);
	/* GET */
	static bool getKeyW() { return keyW; }
	static bool getKeyA() { return keyA; }
	static bool getKeyS() { return keyS; }
	static bool getKeyD() { return keyD; }
private:
	static bool keyW;
	static bool keyA;
	static bool keyS;
	static bool keyD;
};

#endif