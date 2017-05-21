#include "Joystick.h"

bool Joystick::keyW = false;
bool Joystick::keyA = false;
bool Joystick::keyS = false;
bool Joystick::keyD = false;

Joystick::Joystick()
{
}

Joystick::~Joystick()
{
}

bool Joystick::init()
{
	CCLOG("%d %d %d %d", keyA, keyW, keyS, keyD);
	return true;
}

void Joystick::setKeyState(EventKeyboard::KeyCode keyCode, bool state)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		keyW = state;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		keyA = state;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		keyS = state;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		keyD = state;
		break;
	default:
		break;
	}
}
