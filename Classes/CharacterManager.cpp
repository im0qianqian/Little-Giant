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
	startGame(0, 10);
	return true;
}

void CharacterManager::startGame(int ally, int enemy)
{
	createCharacter(kCharacterPlayer);
	for (int i = 0; i < ally; i++)
	{
		createCharacter(kCharacterAlly);
	}
	for (int i = 0; i < enemy; i++)
	{
		createCharacter(kCharacterEnemy);
	}
}

void CharacterManager::pauseGame()
{
}

void CharacterManager::resumeGame()
{
}

Character * CharacterManager::createCharacter(CharacterType characterType)
{
	auto character = Character::create();
	addChild(character);
	if (characterType == kCharacterPlayer)
	{
		_playerCharacter = character;
		_playerCharacter->setDept(-1);
		GameScene::getCamera()->setPosition3D(Vec3(character->getPosition3D().x , 40, character->getPosition3D().z+40));
		GameScene::getCamera()->lookAt(Vec3(character->getPosition3D().x,0, character->getPosition3D().z));
	}
	else
	{
		_enemyCharacter.pushBack(character);
	}
	//character->setTag(characterType);
	return character;
}

