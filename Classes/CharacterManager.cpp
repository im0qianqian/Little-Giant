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
	_listenerKeyboard = EventListenerKeyboard::create();
	_listenerKeyboard->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event *event)
	{
		
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
	des.shape = Physics3DShape::createBox(Vec3(0.5f, 1.0f, 0.5f));	//刚体类型为Box
	auto character = Character::create("Sprite3DTest/box.c3t", &des);
	character->setTexture("images/Icon.png");						//设置材质
	character->setPosition3D(Vec3(0, 10, 0));
	character->setScale(2.0f);
	character->syncNodeToPhysics();
	addChild(character);

	return static_cast<Character*> (character);
}

