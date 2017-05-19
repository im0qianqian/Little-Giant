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
		//Vec3 now=
		switch (keyCode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			GameScene::getCharacterManager()->getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D()+Vec3(-1,0,0));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			GameScene::getCharacterManager()->getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(1, 0, 0));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
			GameScene::getCharacterManager()->getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(0, 0, -1));
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			GameScene::getCharacterManager()->getPlayerCharacter()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() + Vec3(0, 0, 1));
			break;
		default:
			break;
		}
		getPlayerCharacter()->syncNodeToPhysics();
		getPlayerCharacter()->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
		
		log("%d", keyCode);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKeyboard, this);
	return character;
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
	character->setPosition3D(Vec3(0, 10, 0));
	character->setScale(2.0f);
	character->syncNodeToPhysics();
	addChild(character);

	return static_cast<Character*> (character);
}

