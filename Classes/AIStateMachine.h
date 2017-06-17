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
	Character *_character;		// ��ǰ����
	GlobalType _globalType;		// ��������
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
	AIState *_aiState;					//��ǰ״̬
	AIStatePatrol *_aiStatePatrol;		//Ѳ��״̬
	AIStateBeAttack *_aiStateBeAttack;	//�ܵ�����״̬
	AIStateHPLess *_aiStateHPLess;		//Ѫ������״̬
};
#endif