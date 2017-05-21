#include "CharacterManager.h"
#include "GameScene.h"
#include "Joystick.h"

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
	CCLOG("%p", character);
	CCASSERT(character, "character null");
	/*GameScene::getCamera()->setPosition3D(Vec3(150, 150, 150));
	GameScene::getCamera()->lookAt(Vec3::ZERO, Vec3::UNIT_Y);*/

	/*auto rigidBody = static_cast<Physics3DRigidBody*>(character->getPhysicsObj());
	rigidBody->setLinearFactor(Vec3::ONE);
	rigidBody->setLinearVelocity(character);
	rigidBody->setAngularVelocity(Vec3::ZERO);
	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(0.4f);*/

	_listenerKeyboard = EventListenerKeyboard::create();
	_listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		Joystick::setKeyState(keyCode, true);
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
		Vec3 c = Vec3(200.0f*sinf(_angle), 200.0f*sinf(_angley), 200.0f*cosf(_angle));
		//Vec3 c = camera->getPosition3D();
		GameScene::getCamera()->setPosition3D(Vec3(200.0f * sinf(_angle), 200.0f * cosf(_angley), 200.0f * (cosf(_angle) + sinf(_angley))));
		//_camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, -100.0f * cosf(_angle)));
		GameScene::getCamera()->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3::UNIT_Y);
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

