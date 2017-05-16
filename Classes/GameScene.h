#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CharacterManager.h"
#include "WeaponManager.h"
#include "StageManager.h"

USING_NS_CC;
//实现控制各个游戏状态

enum GameStateType	// 游戏状态
{
	kGameStateRuning,	//游戏进行
	kGameStatePause,	//游戏暂停
	kGameStateWin,		//游戏胜利
	kGameStateFail		//游戏失败
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	bool init();
	virtual void onEnterTransitionDidFinish();
	/* 获取当前游戏状态 */
	static GameStateType getGameState() { return _gameState; }
	/* 获取人物管理对象 */
	static CharacterManager* getCharacterManager() { return _characterManager; }
	/* 获取地图管理对象 */
	static StageManager* getStage() { return _stageManager; }
	/* 获取武器管理对象 */
	static WeaponManager* getWeaponManager() { return _weaponManager; }
private:
	static GameStateType _gameState;			//游戏状态
	static CharacterManager *_characterManager;	//人物管理对象
	static StageManager *_stageManager;			//地图管理对象
	static WeaponManager *_weaponManager;		//武器管理对象
};


#endif