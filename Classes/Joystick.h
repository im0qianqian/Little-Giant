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
	virtual bool init() override;
	CREATE_FUNC(Joystick);
	
	/* GET */
	bool getKeyW() const { return _keyW; }
	bool getKeyA() const { return _keyA; }
	bool getKeyS() const { return _keyS; }
	bool getKeyD() const { return _keyD; }

	/* ��ײ�¼� */
	std::function<void(const Physics3DCollisionInfo &ci)> onPhysics3DCollision();

	/* �ݶ���������Ч */
	void createParticle(const Vec3 &pos);

	/* �Ƿ��ǵ�һ�˳��ӽ� */
	bool isFirstView() const { return _isFirstView; }
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
	bool _keyW;
	bool _keyA;
	bool _keyS;
	bool _keyD;
	bool _isFirstView;								//�Ƿ�Ϊ��һ�˳��ӽ�
	EventListenerTouchAllAtOnce* _listenerTouch;	//���ؼ�����
	EventListenerKeyboard* _listenerKeyboard;	//���̼�����
};

#endif