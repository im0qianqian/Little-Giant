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
	/* ��ͣ��Ϸ */
	void pauseGame();
	/* ������Ϸ */
	void resumeGame();
	/* �������*/
	Character* createPlayer();
	/* �������� */
	Character* createEnemy();
private:
	/* �������� */
	Character* createCharacter();
	EventListenerKeyboard* _listenerKeyboard;	//���̼�����
	Character* _playerCharacter;				//�������
	Vector<Character*> _enemyCharacter;			//��������
};
#endif // __CHARACTER_MANAGER_H__
