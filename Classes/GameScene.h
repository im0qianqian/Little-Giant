#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "CharacterManager.h"
#include "WeaponManager.h"
#include "StageManager.h"
#include "AwardManager.h"
#include "AudioManager.h"
#include "DisplayManager.h"
#include "Joystick.h"


USING_NS_CC;
//实现控制各个游戏状态

enum GameStateType	// 游戏状态
{
	kGameStateRuning,	//游戏进行
	kGameStatePause,	//游戏暂停
	kGameStateWin,		//游戏胜利
	kGameStateFail		//游戏失败
};

enum GameModeType	// 游戏模式
{
	kGameModeAdventure,		// 冒险模式（死亡结束）
	kGameModeTimer,			// 计时模式（时间到结束）
	kGameModeNight			// 黑夜模式（死亡结束）
};

class GameScene :public Layer
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	/* 获取当前游戏状态 */
	static GameStateType getGameState() { return _gameState; }
	/* 获取人物管理对象 */
	static CharacterManager* getCharacterManager() { return _characterManager; }
	/* 获取地图管理对象 */
	static StageManager* getStageManager() { return _stageManager; }
	/* 获取武器管理对象 */
	static WeaponManager* getWeaponManager() { return _weaponManager; }
	/* 获取奖励管理对象 */
	static AwardManager *getAwardManager() { return _awardManager; }
	/* 获取声音管理对象 */
	static AudioManager *getAudioManager() { return _audioManager; }
	/* 获取界面管理对象 */
	static DisplayManager *getDisplayManager() { return _displayManager; }
	/* 获取操作管理对象 */
	static Joystick *getJoystick() { return _joystick; }
	/* 获取当前层相机 */
	static Camera *getCamera() { return _camera; }
private:
	static Camera *_camera;						//游戏摄像机(3D)
	static GameStateType _gameState;			//游戏状态
	static CharacterManager *_characterManager;	//人物管理对象
	static StageManager *_stageManager;			//地图管理对象
	static WeaponManager *_weaponManager;		//武器管理对象
	static AwardManager *_awardManager;			//奖励管理对象
	static AudioManager *_audioManager;			//声音管理对象
	static DisplayManager *_displayManager;		//界面显示管理对象
	static Joystick *_joystick;					//操作管理对象
};


#endif