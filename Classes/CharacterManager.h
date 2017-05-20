#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "cocos2d.h"
#include "Character.h"
#include "physics3d\CCPhysics3D.h"

USING_NS_CC;

/* 玩家管理类 */
class CharacterManager :public Layer
{
public:
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	virtual bool init();
	/* 获取玩家人物 */
	Character* getPlayerCharacter() { return _playerCharacter; }
	/* 获取其他玩家 */
	Vector<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/* 创建玩家*/
	Character* createPlayer();
	/* 创建敌人 */
	Character* createEnemy();

	void CharacterManager::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void CharacterManager::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
	void CharacterManager::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
private:
	/* 创建人物 */
	Character* createCharacter();
	EventListenerKeyboard* _listenerKeyboard;	//键盘监听器
	bool isKeyboardPress;						//键盘是否被按下
	Character* _playerCharacter;				//玩家人物
	Vector<Character*> _enemyCharacter;			//其他人物
};
#endif // __CHARACTER_MANAGER_H__
