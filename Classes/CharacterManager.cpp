#include "CharacterManager.h"
#include "GameScene.h"
#include "Global.h"
#include "DisplayManager.h"

CharacterManager::CharacterManager():
	_playerCharacter(nullptr),
	_cachePool(ObjCachePool<EnemyCharacter>(this, CHARACTER_CACHE_SIZE)),
	_enemyCharacter(set<Character*>())
{
	cout << "CharacterManager 构造" << endl;
}

CharacterManager::~CharacterManager()
{
	cout << "CharacterManager 析构" << endl;
}

bool CharacterManager::init()
{
	// 第一步先创建缓存池
	_cachePool.createCachePool();
	// 第二步创建人物
	startGame(0,0);
	scheduleUpdate();
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
	cout << "人物对象全部创建----------------------------------" << endl;
	for (auto i : _enemyCharacter)
	{
		i->initialization();				//登场
	}
}

void CharacterManager::pauseGame()
{
}

void CharacterManager::resumeGame()
{
}

void CharacterManager::createCharacter(CharacterType characterType)
{
	switch (characterType)
	{
	case kCharacterPlayer:
		_playerCharacter = PlayerCharacter::create();
		_playerCharacter->initialization();
		GameScene::getCamera()->setPosition3D(Vec3(_playerCharacter->getPosition3D().x, 50, _playerCharacter->getPosition3D().z + 20));
		GameScene::getCamera()->lookAt(Vec3(_playerCharacter->getPosition3D().x, 0, _playerCharacter->getPosition3D().z));
		addChild(_playerCharacter);
		break;
	default:
		auto character = _cachePool.getFromPool();	//从缓存池中取出人物
		_enemyCharacter.insert(character);
		break;
	}
}

void CharacterManager::addToPool(EnemyCharacter * const & character)
{
	//加入缓存池说明当前人物已死亡
	_cachePool.addToPool(character);
	//从人物列表中删除
	_enemyCharacter.erase(character);
	/*cout << "一个人物已死亡，缓冲池大小：" << _cachePool.getResidualSize() << endl;
	cout << "场上剩余人数：" << _enemyCharacter.size() << endl;*/
}

void CharacterManager::update(float dt)
{
	if (GameScene::getGameMode() != kGameModeTimer)
	{
		if (_enemyCharacter.size() == 0)
		{
			GameScene::getDisplayManager()->showSorceBoard();
		}
	}
}

