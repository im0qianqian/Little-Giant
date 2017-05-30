#include "CharacterManager.h"
#include "GameScene.h"
#include "Joystick.h"
#include "SceneManager.h"

CharacterManager::CharacterManager()
{
}

CharacterManager::~CharacterManager()
{
}
bool CharacterManager::init()
{
	_playerCharacter = createPlayer();
	return true;
}

void CharacterManager::pauseGame()
{
}

void CharacterManager::resumeGame()
{
}

Character * CharacterManager::createPlayer()
{
	auto character = createCharacter();
	GameScene::getCamera()->setPosition3D(Vec3(0,40,40));
	GameScene::getCamera()->lookAt(Vec3::ZERO);
	_listenerKeyboard = EventListenerKeyboard::create();
	_listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		Joystick::setKeyState(keyCode, true);
		/* 方便调试 设置 Debug 模式*/
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			if (SceneManager::getScene()->getPhysics3DWorld()->isDebugDrawEnabled())
				SceneManager::getScene()->getPhysics3DWorld()->setDebugDrawEnable(false);
			else SceneManager::getScene()->getPhysics3DWorld()->setDebugDrawEnable(true);
		}
		/* ----------------------- */
		log("%d", keyCode);
	};
	_listenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		CCLOG("Released~");
		Joystick::setKeyState(keyCode, false);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKeyboard, this);
	CCLOG("----> init");
	//character->init();

	auto listen = EventListenerTouchAllAtOnce::create();
	listen->onTouchesMoved = CC_CALLBACK_2(CharacterManager::onTouchesMoved, this);
	listen->onTouchesEnded = CC_CALLBACK_2(CharacterManager::onTouchesEnded, this);
	listen->onTouchesBegan = CC_CALLBACK_2(CharacterManager::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);

	return character;
}


void CharacterManager::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	event->stopPropagation();
}
void CharacterManager::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
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
		CCLOG("%f %f %f", getPlayerCharacter()->getPosition3D().x, getPlayerCharacter()->getPosition3D().y, getPlayerCharacter()->getPosition3D().z);
		CCLOG("manag %f %f %f", p.x, p.y, p.z);
		p.y = 20;
		getPlayerCharacter()->attack(p);
		event->stopPropagation();
	}
}

void CharacterManager::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	
	if (!touches.empty())
	{
		auto touch = touches[0];
		auto delta = touch->getDelta();
		static float _angle = 0.f;
		static float _angley = 0.f;
		_angle -= CC_DEGREES_TO_RADIANS(delta.x);
		_angley -= CC_DEGREES_TO_RADIANS(delta.y);
		Vec3 cam = getPlayerCharacter()->getPosition3D();
		CCLOG("cam  --> %f %f %f", cam.x, cam.y, cam.z);
		Vec3 c = Vec3(200.0f*sinf(_angle)+ cam.x, 200.0f*sinf(_angley) + cam.y, 200.0f*cosf(_angle) + cam.z);
		//Vec3 c = camera->getPosition3D();
		GameScene::getCamera()->setPosition3D(c);
		//_camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, -100.0f * cosf(_angle)));
		GameScene::getCamera()->lookAt(cam, Vec3::UNIT_Y);
	}
	event->stopPropagation();
	
}





Character * CharacterManager::createEnemy()
{
	return createCharacter();
}

Character * CharacterManager::createCharacter()
{
	auto character = Character::create();
	addChild(character);
	return character;
}

