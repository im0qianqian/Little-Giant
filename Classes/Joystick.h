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

	/* ��ײ�¼� */
	std::function<void(const Physics3DCollisionInfo &ci)> onPhysics3DCollision();
private:
	/* ���̼��� */
	void keyboardListen();
	/* �������� */
	void touchListen();

	/* ���õ�ǰ���̰���״̬ */
	void setKeyState(const EventKeyboard::KeyCode &keyCode, const bool &state);
	/* ��������¼� */
	void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);

	/* һЩ���� */
	bool keyW;
	bool keyA;
	bool keyS;
	bool keyD;
	EventListenerTouchAllAtOnce* _listenerTouch;	//���ؼ�����
	EventListenerKeyboard* _listenerKeyboard;	//���̼�����
};

#endif