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
	startGame(0, 100);
	schedule(schedule_selector(CharacterManager::update), .3f);
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

void CharacterManager::update(float dt)
{
	for (auto i : getEnemyCharacter())
	{
		if (i->getLifeValue() <= 0)
		{
			//getEnemyCharacter().erase(i);
			i->removeFromParent();
		}
	}
}

Character * CharacterManager::createCharacter(CharacterType characterType)
{
	auto character = Character::create();
	if (character != NULL)
	{
		if (characterType == kCharacterPlayer)
		{
			_playerCharacter = character;
			_playerCharacter->setDept(-1);
			GameScene::getCamera()->setPosition3D(Vec3(character->getPosition3D().x, 40, character->getPosition3D().z + 40));
			GameScene::getCamera()->lookAt(Vec3(character->getPosition3D().x, 0, character->getPosition3D().z));
		}
		else
		{
			_enemyCharacter.pushBack(character);
		}
		addChild(character);
	}
	return character;
}

