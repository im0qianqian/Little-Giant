#ifndef __Character_MANAGER_H__
#define __Character_MANAGER_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "Character.h"

USING_NS_CC;

/* 玩家管理类 */
class CharacterManager :public Layer
{
public:
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	/* 获取玩家人物 */
	Character* getPlayerCharacter() { return _playerCharacter; }
	/* 获取其他玩家 */
	Vector<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
<<<<<<< HEAD
	/* 创建玩家 */
	Character* createCharacter(CharacterType characterType);
private:
	//EventListenerKeyboard* _listenerKeyboard;	//键盘监听器
	Character* _playerCharacter;				//玩家人物
	Vector<Character*> _enemyCharacter;			//其他人物
=======
private:
	void createCharacter();
	Character* _playerCharacter;		//玩家人物
	Vector<Character*> _enemyCharacter;	//其他人物
>>>>>>> parent of e11770a... init
};
#endif // __Character_MANAGER_H__
