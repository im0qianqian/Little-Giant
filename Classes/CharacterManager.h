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
	Character* getPlayerCharacter() const { return _playerCharacter; }
	/* 获取其他玩家 */
	set<Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* 开始游戏 创建盟友数量 + 敌人数量 */
	void startGame(const int &ally,const int &enemy);
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/* 添加一个人物对象到缓存池 */
	void addCharacterToPool(Character * const &character);
	enum CharacterType
	{
		kCharacterPlayer,						//玩家
		kCharacterAlly,							//盟友
		kCharacterEnemy							//敌人
	};
	/* 创建人物 */
	Character* createCharacter(CharacterType characterType);
private:
	/* 从缓存池中获取一个人物对象 */
	Character *getCharacterFromPool();
	Character* _playerCharacter;				//玩家人物
	set<Character*> _enemyCharacter;			//其他人物
	const int _cachePoolSize = 100;
	void createCachePool();						// 创建缓存池
	Vector<Character*> _characterCachePool;		// 武器对象缓冲池
};
#endif // __CHARACTER_MANAGER_H__
