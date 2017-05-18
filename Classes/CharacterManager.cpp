#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
}

CharacterManager::~CharacterManager()
{
}

bool CharacterManager::init()
{
	createCharacter(kCharacterPlayer);
	return true;
}

void CharacterManager::pauseGame()
{
}

void CharacterManager::resumeGame()
{
}

Character* CharacterManager::createCharacter(CharacterType characterType)
{
	CCLOG("Character manager");
	/* 创建一个刚体 */
	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//暂定，人物质量设置为50
	des.shape = Physics3DShape::createBox(Vec3(0.5f, 1.0f, 0.5f));	//刚体类型为Box
	auto character = Character::create("Sprite3DTest/box.c3t", &des);
	character->setTexture("images/Icon.png");						//设置材质
	character->setPosition3D(Vec3(0,10,0));
	character->setScale(2.0f);
	character->syncNodeToPhysics();
	addChild(character);
	switch (characterType)
	{
	case kCharacterPlayer:
		/*_listenerKeyboard = EventListenerKeyboard::create();
		_listenerKeyboard->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event)
		{
			CCLOG("%g", keyCode);
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKeyboard, this);*/
		break;
	case kCharacterEnemy:
		break;
	default:
		break;
	}
	GameScene::getCamera()->setPosition3D(Vec3(0, 100, -100));
	GameScene::getCamera()->lookAt(Vec3::ZERO, Vec3::UNIT_Y);
	return static_cast<Character*> (character);
}
