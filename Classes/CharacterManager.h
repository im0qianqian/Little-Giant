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
	/* 添加销毁对象 */
	void addDestroyCharacter(Character *character);
	/* 开始游戏 创建盟友数量 + 敌人数量 */
	void startGame(int ally, int enemy);
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
private:
	/* 销毁已死亡的人物 */
	void destroyDeadCharacters();
	void update(float dt);
	enum CharacterType
	{
		kCharacterPlayer,						//玩家
		kCharacterAlly,							//盟友
		kCharacterEnemy							//敌人
	};
	/* 创建人物 */
	Character* createCharacter(CharacterType characterType);
	Character* _playerCharacter;				//玩家人物
	Vector<Character*> _enemyCharacter;			//其他人物
	Vector<Character*> _destroyList;			//销毁列表
};
#endif // __CHARACTER_MANAGER_H__
