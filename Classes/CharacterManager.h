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



	void CharacterManager::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void CharacterManager::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void CharacterManager::shootBox(const cocos2d::Vec3 &des);
	void CharacterManager::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	/* �������� */
	Character* createCharacter();
	EventListenerKeyboard* _listenerKeyboard;	//���̼�����
	bool isKeyboardPress;						//�����Ƿ񱻰���
	Character* _playerCharacter;				//�������
	Vector<Character*> _enemyCharacter;			//��������
};
#endif // __CHARACTER_MANAGER_H__
