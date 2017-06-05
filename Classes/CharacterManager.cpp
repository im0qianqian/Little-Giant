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
	// 第一步先创建缓存池
	createCachePool();
	// 第二步创建人物
	startGame(0,50);
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
	cout << "成功从缓存池中获取一个人物对象：" << character << endl;
	cout << "人物缓存池大小剩余：" << _characterCachePool.size() << endl;
	return character;
}

void CharacterManager::addCharacterToPool(Character * const & character)
{
	//加入缓存池说明当前人物已死亡
	_characterCachePool.pushBack(character);
	//从人物列表中删除
	_enemyCharacter.erase(character);
	cout << "一个人物已死亡，缓冲池大小：" << _characterCachePool.size() << endl;
	cout << "场上剩余人数：" << _enemyCharacter.size() << endl;
}

Character * CharacterManager::createCharacter(CharacterType characterType)
{
	auto character = getCharacterFromPool();	//从缓存池中取出人物
	if (character != NULL)
	{
		character->initialization();					//登场
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
	// 缓存池清空
	_characterCachePool.clear();
	for (auto i = 0; i < _cachePoolSize; i++)
	{
		Character* character = Character::create();
		_characterCachePool.pushBack(character);
		addChild(character);	//添加到图层
	}
	cout << "人物缓存池大小剩余：" << _characterCachePool.size() << endl;
}

