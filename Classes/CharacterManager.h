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
	Character* getPlayerCharacter() { return _playerCharacter; }
	/* ��ȡ������� */
	Vector<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* ������ٶ��� */
	void addDestroyCharacter(Character *character);
	/* ��ʼ��Ϸ ������������ + �������� */
	void startGame(int ally, int enemy);
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
private:
	/* ���������������� */
	void destroyDeadCharacters();
	void update(float dt);
	enum CharacterType
	{
		kCharacterPlayer,						//���
		kCharacterAlly,							//����
		kCharacterEnemy							//����
	};
	/* �������� */
	Character* createCharacter(CharacterType characterType);
	Character* _playerCharacter;				//�������
	Vector<Character*> _enemyCharacter;			//��������
	Vector<Character*> _destroyList;			//�����б�
};
#endif // __CHARACTER_MANAGER_H__
