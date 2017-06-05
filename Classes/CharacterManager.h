#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "cocos2d.h"
#include "Character.h"
#include "ObjCachePool.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

/* ��ҹ����� */
class CharacterManager :public Layer
{
public:
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	virtual bool init();
	/* ��ȡ������� */
	Character* getPlayerCharacter() const { return _playerCharacter; }
	/* ��ȡ������� */
	std::set<Character*> &getEnemyCharacter() { return _enemyCharacter; }
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
	Character* createCharacter(CharacterType characterType);
	/* ���һ��������󵽻���� */
	void addToPool(Character * const &character);
private:
	Character* _playerCharacter;						//�������
	std::set<Character*> _enemyCharacter;				//��������
	ObjCachePool<Character> _cachePool;					//�����
};
#endif // __CHARACTER_MANAGER_H__
