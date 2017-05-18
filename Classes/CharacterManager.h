#ifndef __Character_MANAGER_H__
#define __Character_MANAGER_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "Character.h"

USING_NS_CC;

/* ��ҹ����� */
class CharacterManager :public Layer
{
public:
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	/* ��ȡ������� */
	Character* getPlayerCharacter() { return _playerCharacter; }
	/* ��ȡ������� */
	Vector<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
<<<<<<< HEAD
	/* ������� */
	Character* createCharacter(CharacterType characterType);
private:
	//EventListenerKeyboard* _listenerKeyboard;	//���̼�����
	Character* _playerCharacter;				//�������
	Vector<Character*> _enemyCharacter;			//��������
=======
private:
	void createCharacter();
	Character* _playerCharacter;		//�������
	Vector<Character*> _enemyCharacter;	//��������
>>>>>>> parent of e11770a... init
};
#endif // __Character_MANAGER_H__
