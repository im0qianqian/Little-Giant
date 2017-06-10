#include "CharacterManager.h"
#include "GameScene.h"
#include "Global.h"

CharacterManager::CharacterManager():
	_playerCharacter(nullptr),
	_cachePool(ObjCachePool<Character>(this, CHARACTER_CACHE_SIZE))
{
	_enemyCharacter.clear();
}

CharacterManager::~CharacterManager()
{
}
bool CharacterManager::init()
{
	// ��һ���ȴ��������
	_cachePool.createCachePool();
	// �ڶ�����������
	startGame(0,100);
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

Character * CharacterManager::createCharacter(CharacterType characterType)
{
	auto character = _cachePool.getFromPool();	//�ӻ������ȡ������
	if (character != NULL)
	{
		character->initialization();					//�ǳ�
		if (characterType == kCharacterPlayer)
		{
			_playerCharacter = character;
			_playerCharacter->setDept(-1);
			_playerCharacter->setName("qianqian");		// ���������Լ�������
			GameScene::getCamera()->setPosition3D(Vec3(character->getPosition3D().x, 50, character->getPosition3D().z+20));
			GameScene::getCamera()->lookAt(Vec3(character->getPosition3D().x, 0, character->getPosition3D().z));
		}
		else
		{
			_enemyCharacter.insert(character);
		}
	}
	return character;
}

void CharacterManager::addToPool(Character * const & character)
{
	//���뻺���˵����ǰ����������
	_cachePool.addToPool(character);
	//�������б���ɾ��
	_enemyCharacter.erase(character);
	/*cout << "һ������������������ش�С��" << _cachePool.getResidualSize() << endl;
	cout << "����ʣ��������" << _enemyCharacter.size() << endl;*/
}

