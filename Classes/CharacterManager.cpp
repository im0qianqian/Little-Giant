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
	// ��һ���ȴ��������
	createCachePool();
	// �ڶ�����������
	startGame(0,0);
	schedule(schedule_selector(CharacterManager::update), .3f);
	return true;
}

void CharacterManager::startGame(const int &ally, const int &enemy)
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

Character * CharacterManager::getCharacterFromPool()
{
	Character* character = nullptr;
	if (!_characterCachePool.empty())
	{
		character = _characterCachePool.back();
		_characterCachePool.popBack();
	}
	cout << "�ɹ��ӻ�����л�ȡһ���������" << character << endl;
	cout << "���ﻺ��ش�Сʣ�ࣺ" << _characterCachePool.size() << endl;
	return character;
}

void CharacterManager::addCharacterToPool(Character * const & character)
{
	//���뻺���˵����ǰ����������
	_characterCachePool.pushBack(character);
	//�������б���ɾ��
	_enemyCharacter.erase(character);
	cout << "һ������������������ش�С��" << _characterCachePool.size() << endl;
	cout << "����ʣ��������" << _enemyCharacter.size() << endl;
}

Character * CharacterManager::createCharacter(CharacterType characterType)
{
	auto character = getCharacterFromPool();	//�ӻ������ȡ������
	if (character != NULL)
	{
		character->initialization();					//�ǳ�
		if (characterType == kCharacterPlayer)
		{
			_playerCharacter = character;
			_playerCharacter->setDept(-1);
			GameScene::getCamera()->setPosition3D(Vec3(character->getPosition3D().x+100, 50, character->getPosition3D().z + 100));
			GameScene::getCamera()->lookAt(Vec3(character->getPosition3D().x, 0, character->getPosition3D().z));
		}
		else
		{
			_enemyCharacter.insert(character);
		}
	}
	return character;
}

void CharacterManager::createCachePool()
{
	// ��������
	_characterCachePool.clear();
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		Character* character = Character::create();
		_characterCachePool.pushBack(character);
		addChild(character);	//��ӵ�ͼ��
	}
	cout << "���ﻺ��ش�Сʣ�ࣺ" << _characterCachePool.size() << endl;
}

