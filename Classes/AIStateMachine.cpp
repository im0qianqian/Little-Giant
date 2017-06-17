#include "AIStateMachine.h"
#include "Character.h"
#include "GameScene.h"

AIStateMachine::AIStateMachine():
	_aiStatePatrol(nullptr),
	_aiStateBeAttack(nullptr),
	_aiStateHPLess(nullptr),
	_aiState(nullptr)
{
}

AIStateMachine::AIStateMachine(Character * const & character)
{
	/* ��������״̬ */
	_aiStatePatrol = new AIStatePatrol(character);
	_aiStateBeAttack = new AIStateBeAttack(character);
	_aiStateHPLess = new AIStateHPLess(character);
	_aiState = _aiStatePatrol;
}

AIStateMachine::~AIStateMachine()
{
}

void AIStateMachine::run()
{
	_aiState->run();
}

void AIStateMachine::changeState(const aiState & state)
{
	switch (state)
	{
	case kAIStatePatrol:
		_aiState = _aiStatePatrol;
		break;
	case kAIStateBeAttack:
		_aiState = _aiStateBeAttack;
		break;
	case kAIStateHPLess:
		_aiState = _aiStateHPLess;
		break;
	default:
		break;
	}
}

AIState::AIState():
	_character(nullptr),
	_globalType(kGlobalCharacter)
{
}

AIState::AIState(Character * const & character):
	_character(character),
	_globalType(kGlobalCharacter)
{
}

void AIState::findPath()
{
	typedef enum
	{
		kDirectionUp,
		kDirectionDown,
		kDirectionLeft,
		kDirectionRight
	}directionType;
	int cMap[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH];
	bool isVisted[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH] = { false };
	auto map = GameScene::getStageManager()->getMap();
	GameScene::getStageManager()->getCMap(cMap);
	struct node
	{
		node(){}
		node(const int &x,const int &y,const directionType &d):
			_x(x),
			_y(y),
			_direction(d)
		{}
		int _x, _y;
		directionType _direction;
	};
	/* �����ݶ�BFS ���Ժ��Ż�ΪA* */
	const int mv[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
	Vec3 cPos = _character->getPosition3D();
	Vec2 pos = Vec2(int((cPos.z + WORLD_WIDTH / 2)*MAPS_FILE_WIDTH / WORLD_WIDTH), int((cPos.x + WORLD_LENGTH / 2)*MAPS_FILE_LENGTH / WORLD_LENGTH));
	auto judPos = [&](shared_ptr<node> const &n)		//�жϵ��Ƿ��ڵ�ͼ��
	{
		if (n->_x < 0 || n->_x >= MAPS_FILE_WIDTH || n->_y < 0 || n->_y >= WORLD_LENGTH|| map[n->_x][n->_y]!=0)
			return false;
		return true;
	};
	queue<shared_ptr<node>> que;
	for (int i = 0; i < 4; i++)		//��ʼ�ĸ�����
	{
		shared_ptr<node> n(new node(pos.x+mv[i][0], pos.y + mv[i][1], directionType(i)));
		if (judPos(n))
		{
			isVisted[n->_x][n->_y] = true;
			que.push(n);
		}
	}
	while (!que.empty())
	{
		auto p = que.front();
		que.pop();
		if (cMap[p->_x][p->_y] == int(_globalType))	// ������ڵ�ǰ����Ѱ�ҵĶ���
		{
			/*cout << "----------------> "<<p->_direction << endl;
			for (int i = 0; i < MAPS_FILE_WIDTH; i++)
			{
				for (int j = 0; j < MAPS_FILE_LENGTH; j++)
				{
					cout << cMap[i][j];
				}
				cout << endl;
			}
			cout << "----------------------------------------------------" << endl;*/
			Vec3 dir;
			switch (p->_direction)
			{
			case kDirectionUp:
				dir = Vec3(0, 0, -1);
				break;
			case kDirectionDown:
				dir = Vec3(0, 0, 1);
				break;
			case kDirectionLeft:
				dir = Vec3(-1, 0, 0);
				break;
			case kDirectionRight:
				dir = Vec3(1, 0, 0);
				break;
			default:
				break;
			}
			_character->setDirection(dir);
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			shared_ptr<node> n(new node(p->_x + mv[i][0], p->_y + mv[i][1], p->_direction));
			if (judPos(n)&&!isVisted[n->_x][n->_y])
			{
				que.push(n);
				isVisted[n->_x][n->_y] = true;
			}
		}
	}
}

AIStatePatrol::AIStatePatrol()
{
}

AIStatePatrol::AIStatePatrol(Character * const & character):
	AIState(character)
{
}

void AIStatePatrol::run()
{
	//cout << "ת�Ƶ�Ѳ��״̬" << endl;
	findPath();
	static int tot = 0;
	if (abs(tot++) % 2==1)	//���ת��״̬
	{
		/* ״̬��ת�Ƶ�Ѱ�ҵ��˽��й��� */
		dynamic_cast<EnemyCharacter*>(getCharacter())->getAIStateMachine()->changeState(AIStateMachine::kAIStateBeAttack);
	}
	else
	{
		dynamic_cast<EnemyCharacter*>(getCharacter())->getAIStateMachine()->changeState(AIStateMachine::kAIStateHPLess);
	}
}

AIStateBeAttack::AIStateBeAttack()
{
}

AIStateBeAttack::AIStateBeAttack(Character * const & character) :
	AIState(character)
{
}

void AIStateBeAttack::run()
{
	//cout << "ת�Ƶ�����״̬" << endl;
	Vec3 minn = Vec3::ZERO;
	minn = GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() - getCharacter()->getPosition3D();
	auto other = GameScene::getCharacterManager()->getEnemyCharacter();

	int len = other.size();
	for (auto i : other)
	{
		if (i != getCharacter() && (i->getPosition3D() - getCharacter()->getPosition3D()).length() < minn.length())
		{
			minn = i->getPosition3D() - getCharacter()->getPosition3D();
		}
	}
	minn.y = 0;
	if (minn.length() < 20.0)	//�ҵ�����
	{
		getCharacter()->attack(minn + getCharacter()->getPosition3D());
		getCharacter()->setDirection(minn.getNormalized());
		if (minn.length() < 10.0)
		{
			getCharacter()->setDirection(Vec3::ZERO);
		}
	}
	else
	{
		setGlobalType(kGlobalCharacter);	//û���ҵ����ˣ�Ѳ�߽���Ѱ�ҵ���
		//����ת�Ƶ�Ѳ��״̬
		dynamic_cast<EnemyCharacter*>(getCharacter())->getAIStateMachine()->changeState(AIStateMachine::kAIStatePatrol);
	}
}

AIStateHPLess::AIStateHPLess()
{
}

AIStateHPLess::AIStateHPLess(Character * const & character) :
	AIState(character)
{
}

void AIStateHPLess::run()
{
	//cout << "ת�Ƶ���Ѫ״̬" << endl;
	Vec3 minn = Vec3::ONE*(1 << 10);
	auto allAward = GameScene::getAwardManager()->getAllAward();
	for (auto i : allAward)
	{
		if ((i->getPosition3D() - getCharacter()->getPosition3D()).length() < minn.length())
		{
			minn = i->getPosition3D() - getCharacter()->getPosition3D();
		}
	}
	minn.y = 0;
	if (minn.length() < 20)				//�ҵ�����
	{
		getCharacter()->setDirection(minn.getNormalized());
	}
	else								//����ת�Ƶ�Ѳ��״̬
	{
		setGlobalType(kGlobalAward);	//��Ѫ����ʹѲ��ҲҪѰ�ҽ���
		dynamic_cast<EnemyCharacter*>(getCharacter())->getAIStateMachine()->changeState(AIStateMachine::kAIStatePatrol);
	}
}
