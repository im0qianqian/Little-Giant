#ifndef __CHARACTER_MANAGER_H__
#define __CHARACTER_MANAGER_H__

#include "cocos2d.h"
#include "Character.h"
#include "ObjCachePool.h"

USING_NS_CC;

/* 玩家管理类 */
class CharacterManager :public Layer
{
public:
	CharacterManager();
	~CharacterManager();
	CREATE_FUNC(CharacterManager);
	virtual bool init() override;
	/* 获取玩家人物 */
	Character* getPlayerCharacter() const { return _playerCharacter; }
	/* 获取其他玩家 */
	std::set <Character*> &getEnemyCharacter() { return _enemyCharacter; }
	/* 开始游戏 创建盟友数量 + 敌人数量 */
	void startGame(const int &ally,const int &enemy);
	/* 暂停游戏 */
	void pauseGame();
	/* 继续游戏 */
	void resumeGame();
	/* 枚举变量人物类型 */
	enum CharacterType
	{
		kCharacterPlayer,						//玩家
		kCharacterAlly,							//盟友
		kCharacterEnemy							//敌人
	};
	/* 创建人物 */
	void createCharacter(CharacterType characterType);
	/* 添加一个人物对象到缓存池 */
	void addToPool(EnemyCharacter * const &character);
private:
	Character* _playerCharacter;						//玩家人物
	std::set <Character*> _enemyCharacter;				//其他人物
	ObjCachePool<EnemyCharacter> _cachePool;			//缓存池
};
#endif // __CHARACTER_MANAGER_H__
