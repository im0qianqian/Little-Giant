#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "cocos2d.h"
#include "Character.h"
#include "ObjCachePool.h"

USING_NS_CC;

/* ��ҹ����� */
class CharacterManager :public Layer
{
public:
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	bool init();
	/* ��ȡ������� */
	Character* getPlayerCharacter() const { return _playerCharacter; }
	/* ��ȡ������� */
	std::set <Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* ��ʼ��Ϸ ������������ + �������� */
	void startGame(const int &ally,const int &enemy);
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	enum CharacterType
	{
		kCharacterPlayer,						//���
		kCharacterAlly,							//����
		kCharacterEnemy							//����
	};
	/* �������� */
	void createCharacter(CharacterType characterType);
	/* ���һ��������󵽻���� */
	void addToPool(EnemyCharacter * const &character);
private:
	Character* _playerCharacter;						//�������
	std::set <Character*> _enemyCharacter;				//��������
	ObjCachePool<EnemyCharacter> _cachePool;			//�����
};
#endif // __CHARACTER_MANAGER_H__
