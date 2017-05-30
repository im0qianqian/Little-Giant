#include "Joystick.h"
#include "SceneManager.h"
#include "GameScene.h"

Joystick::Joystick() :
	keyW(false),
	keyA(false),
	keyS(false),
	keyD(false),
	_listenerKeyboard(nullptr),
	_listenerTouch(nullptr)
{
}

Joystick::~Joystick()
{
}

bool Joystick::init()
{
	keyboardListen();
	touchListen();
	physicsListen();
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


void Joystick::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	event->stopPropagation();
}

void Joystick::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	CCLOG("on Touches ended!!!");
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocationInView();
		Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
		nearP = GameScene::getCamera()->unproject(nearP);
		farP = GameScene::getCamera()->unproject(farP);
		Vec3 dir(farP - nearP);
		float dist = 0.0f;
		float ndd = Vec3::dot(Vec3(0, 1, 0), dir);
		float ndo = Vec3::dot(Vec3(0, 1, 0), nearP);
		dist = (0 - ndo) / ndd;
		Vec3 p = nearP + dist *  dir;
		//CCLOG("%f %f %f", getPlayerCharacter()->getPosition3D().x, getPlayerCharacter()->getPosition3D().y, getPlayerCharacter()->getPosition3D().z);
		//CCLOG("manag %f %f %f", p.x, p.y, p.z);
		p.y = 20;
		GameScene::getCharacterManager()->getPlayerCharacter()->attack(p);
		event->stopPropagation();
	}
}

void Joystick::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	if (!touches.empty())
	{
		auto touch = touches[0];
		auto delta = touch->getDelta();
		static float _angle = 0.f;
		static float _angley = 0.f;
		_angle -= CC_DEGREES_TO_RADIANS(delta.x);
		_angley -= CC_DEGREES_TO_RADIANS(delta.y);
		Vec3 cam = GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D();
		//CCLOG("cam  --> %f %f %f", cam.x, cam.y, cam.z);
		//Vec3 c = Vec3(200.0f*sinf(_angle)+ cam.x, 200.0f*sinf(_angley) + cam.y, 200.0f*cosf(_angle) + cam.z);
		Vec3 c = Vec3(50.0f * sinf(_angle) + cam.x, 20.0f + cam.y, -50.0f * cosf(_angle) + cam.z);
		//Vec3 c = camera->getPosition3D();
		GameScene::getCamera()->setPosition3D(c);
		//_camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, -100.0f * cosf(_angle)));
		GameScene::getCamera()->lookAt(cam, Vec3::UNIT_Y);
	}
	event->stopPropagation();

}

void Joystick::keyboardListen()
{
	/* 创建键盘监听器 */
	_listenerKeyboard = EventListenerKeyboard::create();
	/* 键盘被按下 */
	_listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		setKeyState(keyCode, true);
		/* 方便调试 设置 Debug 模式*/
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			if (SceneManager::getScene()->getPhysics3DWorld()->isDebugDrawEnabled())
				SceneManager::getScene()->getPhysics3DWorld()->setDebugDrawEnable(false);
			else SceneManager::getScene()->getPhysics3DWorld()->setDebugDrawEnable(true);
		}
		/* ----------------------- */
		log("Keyboard %d Pressed~", keyCode);
	};
	/* 键盘弹起 */
	_listenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		CCLOG("Keyboard %d Released~", keyCode);
		setKeyState(keyCode, false);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKeyboard, this);
}

void Joystick::touchListen()
{
	_listenerTouch = EventListenerTouchAllAtOnce::create();
	_listenerTouch->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
	_listenerTouch->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
	_listenerTouch->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerTouch, this);
}

void Joystick::physicsListen()
{
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact& contact)
	{
		/*auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

		if (spriteA && spriteA->getTag() == 1
			&& spriteB && spriteB->getTag() == 1)
		{
			spriteA->setColor(Color3B::YELLOW);
			spriteB->setColor(Color3B::YELLOW);
		}
		*/
		log("-------------------------------------------------------------");
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	/*auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Joystick::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);*/
	CCLOG("zhu ce cheng gong");
}

bool Joystick::onContactBegin(const PhysicsContact& contact)
{
	CCLOG("peng zhuang~~~~~~~");
	return true;
}