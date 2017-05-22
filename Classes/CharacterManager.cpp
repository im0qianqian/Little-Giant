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
	GameScene::getCamera()->setPosition3D(Vec3(0, 40, 40));
	GameScene::getCamera()->lookAt(Vec3::ZERO);
	//CCLOG("----> init");
	//schedule(schedule_selector(character->update), 1.0f);
	return character;
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

