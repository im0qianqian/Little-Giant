#include "CharacterManager.h"
#include "GameScene.h"
#include "Global.h"

CharacterManager::CharacterManager():
	_playerCharacter(nullptr),
	_cachePool(ObjCachePool<EnemyCharacter>(this, CHARACTER_CACHE_SIZE)),
	_enemyCharacter(set<Character*>())
{
}

CharacterManager::~CharacterManager()
{
}

bool CharacterManager::init()
{
	// ��һ���ȴ��������
	_cachePool.createCachePool();
	// �ڶ�����������
	startGame(0,5);
	//schedule(schedule_selector(CharacterManager::update), .3f);
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
		auto character = _cachePool.getFromPool();	//�ӻ������ȡ������
		character->initialization();				//�ǳ�
		_enemyCharacter.insert(character);
		break;
	}
}

void CharacterManager::addToPool(EnemyCharacter * const & character)
{
	//���뻺���˵����ǰ����������
	_cachePool.addToPool(character);
	//�������б���ɾ��
	_enemyCharacter.erase(character);
	cout << "һ������������������ش�С��" << _cachePool.getResidualSize() << endl;
	cout << "����ʣ��������" << _enemyCharacter.size() << endl;
}

