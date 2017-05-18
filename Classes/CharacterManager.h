#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "Character.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

/* ��ҹ����� */
class CharacterManager :public Layer
{
public:
	enum CharacterType
	{
		kCharacterPlayer,
		kCharacterEnemy
	};
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	virtual bool init();
	/* ��ȡ������� */
	Character* getPlayerCharacter() { return _playerCharacter; }
	/* ��ȡ������� */
	Vector<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/* ������� */
	Character* createCharacter(CharacterType characterType);
private:
	//EventListenerKeyboard* _listenerKeyboard;	//���̼�����
	Character* _playerCharacter;				//�������
	Vector<Character*> _enemyCharacter;			//��������
};
#endif // __CHARACTER_MANAGER_H__
