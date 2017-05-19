#include "CharacterManager.h"
#include "GameScene.h"

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
		isKeyboardPress = true;
		//while (isKeyboardPress)
		{
			switch (keyCode)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
				getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(-1, 0, 0));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
				getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(1, 0, 0));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
				getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(0, 0, -1));
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
				getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(0, 0, 1));
				break;
			default:
				break;
			}
			getPlayerCharacter()->syncNodeToPhysics();
			log("%d", keyCode);
		}
	};
	_listenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		CCLOG("Released~");
		isKeyboardPress = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKeyboard, this);

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
		//CCLOG("%f %f %f", _targetPos.x, _targetPos.y, _targetPos.z);
		CCLOG("%f %f %f", p.x, p.y, p.z);
		p.y = 20;
		shootBox(p);
		event->stopPropagation();
	}
}

void CharacterManager::shootBox(const cocos2d::Vec3 &des)
{
	Physics3DRigidBodyDes rbDes;
	Vec3 sPos = getPlayerCharacter()->getPosition3D();
	Vec3 linearVel = des - sPos;
	linearVel.y = 0;
	linearVel.normalize();
	linearVel *= 100.0f;
	CCLOG("%f %f %f", linearVel.x, linearVel.y, linearVel.z);
	rbDes.originalTransform.translate(sPos);
	rbDes.mass = 1.f;
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));
	auto sprite = PhysicsSprite3D::create("Sprite3DTest/box.c3t", &rbDes);
	sprite->setTexture("images/Icon.png");

	auto rigidBody = static_cast<Physics3DRigidBody*>(sprite->getPhysicsObj());
	rigidBody->setLinearFactor(Vec3::ONE);
	rigidBody->setLinearVelocity(linearVel);
	rigidBody->setAngularVelocity(Vec3::ZERO);
	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(0.4f);

	this->addChild(sprite);
	linearVel.normalize();
	sPos += linearVel;
	sprite->setPosition3D(sPos);
	sprite->setScale(0.5f);
	sprite->syncNodeToPhysics();

	//optimize, only sync node to physics
	sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NODE_AND_NODE); //sync node to physics
												   //sprite->setCameraMask((unsigned short)CameraFlag::USER1);
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
	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//暂定，人物质量设置为50
	des.shape = Physics3DShape::createBox(Vec3(1.0f, 2.0f, 1.0f));	//刚体类型为Box
	auto character = Character::create("Sprite3DTest/box.c3t", &des);
	character->setTexture("images/Icon.png");						//设置材质
	character->setPosition3D(Vec3(0, 100, 0));
	character->setScale(2.0f);
	character->syncNodeToPhysics();
	addChild(character);

	return static_cast<Character*> (character);
}

