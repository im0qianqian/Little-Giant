#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "cocos2d.h"
#include "Character.h"
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
	set<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* ��ʼ��Ϸ ������������ + �������� */
	void startGame(const int &ally,const int &enemy);
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/* ���һ��������󵽻���� */
	void addCharacterToPool(Character * const &character);
	enum CharacterType
	{
		kCharacterPlayer,						//���
		kCharacterAlly,							//����
		kCharacterEnemy							//����
	};
	/* �������� */
	Character* createCharacter(CharacterType characterType);
private:
	/* �ӻ�����л�ȡһ��������� */
	Character *getCharacterFromPool();
	Character* _playerCharacter;				//�������
	set<Character*> _enemyCharacter;			//��������
	const int _cachePoolSize = 100;				// ���������������ͬʱ���ڶ������
	void createCachePool();						// ���������
	Vector<Character*> _characterCachePool;		// �������󻺳��
};
#endif // __CHARACTER_MANAGER_H__
