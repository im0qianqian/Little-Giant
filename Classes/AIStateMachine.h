#ifndef __AI_STATE_MACHINE_H__
#define __AI_STATE_MACHINE_H__

#include "cocos2d.h"
#include "Global.h"
USING_NS_CC;
class Character;

class AIState
{
public:
	AIState();
	AIState(Character *const &character);
	virtual void run() = 0;
protected:
	void findPath();
	Character *getCharacter() { return _character; }
	void setGlobalType(const GlobalType &globalType) { _globalType = globalType; }
private:
	Character *_character;		// 当前人物
	GlobalType _globalType;		// 对象类型
};

class AIStatePatrol :public AIState
{
public:
	AIStatePatrol();
	AIStatePatrol(Character *const &character);
	virtual void run() override;
};

class AIStateBeAttack :public AIState
{
public:
	AIStateBeAttack();
	AIStateBeAttack(Character *const &character);
	virtual void run() override;
};

class AIStateHPLess :public AIState
{
public:
	AIStateHPLess();
	AIStateHPLess(Character *const &character);
	virtual void run() override;
};

class AIStateMachine
{
public:
	AIStateMachine();
	AIStateMachine(Character *const &character);
	~AIStateMachine();
	void run();
	typedef enum 
	{
		kAIStatePatrol,
		kAIStateBeAttack,
		kAIStateHPLess
	}aiState;
	void changeState(const aiState &state);
private:
	AIState *_aiState;					//当前状态
	AIStatePatrol *_aiStatePatrol;		//巡逻状态
	AIStateBeAttack *_aiStateBeAttack;	//受到攻击状态
	AIStateHPLess *_aiStateHPLess;		//血量不足状态
};
#endif