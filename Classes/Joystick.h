#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h"

USING_NS_CC;

class Joystick : public Node
{
public:
	Joystick();
	~Joystick();
	virtual bool init();
	CREATE_FUNC(Joystick);
	
	/* GET */
	bool getKeyW() { return keyW; }
	bool getKeyA() { return keyA; }
	bool getKeyS() { return keyS; }
	bool getKeyD() { return keyD; }
	
private:
	/* ¼üÅÌ¼àÌı */
	void keyboardListen();
	/* ´¥ÆÁ¼àÌı */
	void touchListen();
	/* ÉèÖÃµ±Ç°¼üÅÌ°´¼ü×´Ì¬ */
	void setKeyState(EventKeyboard::KeyCode keyCode, bool state);
	/* Êó±êÈıÖÖÊÂ¼ş */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	/* Ò»Ğ©°´¼ü */
	bool keyW;
	bool keyA;
	bool keyS;
	bool keyD;
	EventListenerTouchAllAtOnce* _listenerTouch;	//´¥¿Ø¼àÌıÆ÷
	EventListenerKeyboard* _listenerKeyboard;	//¼üÅÌ¼àÌıÆ÷
};

#endif