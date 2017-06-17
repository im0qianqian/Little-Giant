#include "Character.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Joystick.h"
#include "Weapons.h"
#include "Award.h"
#include "WeaponManager.h"
#include "AIStateMachine.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

USING_NS_CC;

Character::Character() :
	_dept(0),
	_lifeValue(INITIAL_LIFE_VALUE),
	_experience(0),
	_sorce(0),
	_weaponType(kWeaponArrow),
	_isDie(true),
	_attribute(Attribute()),
	_hpSlider(nullptr),
	_direction(Vec3::ZERO),
	_lastAttackTime(0),
	_topName(nullptr)
{
	// �������������ǩ
	setTag(kGlobalCharacter);
}

Character::~Character()
{
	// ��������
	_isDie = true;
	// �����ȴ��߳̽���
	cout << this << " clean up ����" << endl;
	_threadMutex.lock();
	cout << this << " clean up �����ɹ�~" << endl;
	cout << this << " clean up ����" << endl;
	_threadMutex.unlock();
	cout << this << " clean up �����ɹ�~" << endl;
	cout << this << " �ѱ�����" << endl;
	cout << "----------------------" << endl;
}

void Character::addLifeValue(const float &add)
{
	if (add >= 0)
	{
		// ��Ѫʱ���ӻָ������ӳ�
		_lifeValue += min(INITIAL_LIFE_VALUE, add*getAttribute().getRestoringAbility());
	}
	else
	{
		// ��Ѫʱ�������������������˺�
		_lifeValue += min(add + getAttribute().getDefensiveForce(), 0);
	}
	_hpSlider->setPercent(_lifeValue);			//����Ѫ����
}

void Character::addExperience(const int &add)
{
	_experience += add*getAttribute().getEmpiricalAcquisition();
}

void Character::addSorce(const int &add)
{
	_sorce += add;
}

void Character::attack(const Vec3 &pos)
{
	const float attackTimeInterval = 600.f / getAttribute().getAttackSpeed();		// ����ʱ����
	int currentTime = GetTickCount64();												// ��ȡ��ǰʱ��
	if (currentTime - _lastAttackTime >= attackTimeInterval)						//������Թ���
	{
		_lastAttackTime = currentTime;												// �������һ�ι���ʱ��
		GameScene::getWeaponManager()->createWeapon(kWeaponArrow, this, getPosition3D(), pos);
	}
}

void Character::move()
{
	/* ��ȡ������� */
	auto s = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	/* �������ٶ�Ϊ�����ƶ��ٶ�*����������Y���򱣳ֺ�ԭ��һ�� */
	s->setLinearVelocity(getAttribute().getMovingSpeed()*getDirection() + Vec3(0, s->getLinearVelocity().y, 0));
}

bool Character::init()
{
	bool flag = false;
	do
	{
		/* �����ǳ�ʼ������ */
		if (initWithFile("Sprite3DTest/box.c3t"))
		{
			setTexture("images/Icon.png");

			Physics3DRigidBodyDes des;
			des.mass = 50.f;			//�ݶ���������������Ϊ50
			des.shape = Physics3DShape::createBox(Vec3(2.0f, 2.0f, 2.0f));	//�����С

			auto obj = Physics3DRigidBody::create(&des);

			_physicsComponent = Physics3DComponent::create(obj);

			addComponent(_physicsComponent);

			_contentSize = getBoundingBox().size;

			obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// ������ײ��Ļص�����

			obj->setUserData(this);

			setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);	//Ӧ��ͬ��

			setScale(2.f);		//���ô�С
			createHpBar();		//����Ѫ����

			flag = true;
		}
	} while (false);
	return flag;
}

void Character::initialization()
{
	// ��ʼ��ֵ
	_lifeValue = INITIAL_LIFE_VALUE;
	_experience = 0;
	// ������Ǽ�ʱģʽ���������
	if (GameScene::getGameMode() != kGameModeTimer)
		_sorce = 0;
	_attribute.init();
	_weaponType = kWeaponArrow;
	_dept = 0;
	_hpSlider->setPercent(_lifeValue);		//����Ѫ����
	_lastAttackTime = 0;					//����ʱ����
	_direction = Vec3::ZERO;				//��ʼ���߷���

	thread([this] {							//�첽���� isDie ����������������AI�߳�
		_threadMutex.lock();
		_isDie = false;						//����
		thread(&Character::moveModule, this).detach();	//��������AI�߳�
		_threadMutex.unlock();
	}).detach();


	// �������λ�ò�ͬ��
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2.0, WORLD_HEIGHT, rand() % WORLD_WIDTH - WORLD_WIDTH / 2.0));
	syncNodeToPhysics();
}

void Character::collisionWithWeapon(Weapons * const & weapon)
{
	if (isDie() || weapon->isDeleted())return;	// ���ĳ���Ѿ�������
	// �����ܵ�����
	beAttacked(weapon);
	//cout << this << " �ܵ����� " << weapon << " �Ĺ���������" << endl;
}

void Character::collisionWithAward(Award * const & award)
{
	[this]()
	{
		auto rootps = PUParticleSystem3D::create("scripts/flareShield.pu");
		if (rootps == nullptr)return;
		rootps->setCameraMask((short int)CameraFlag::USER1);
		rootps->setPosition3D(getPosition3D());
		rootps->setScale(.5f);
		GameScene::getCharacterManager()->addChild(rootps);
		rootps->runAction(Sequence::create(CCDelayTime::create(10.f), CallFunc::create([=]() {
			rootps->removeFromParent();
		}), nullptr));
		rootps->startParticleSystem();
	}();
}

void Character::collisionWithStage()
{
}

void Character::beAttacked(Weapons *const &weapon)
{
	// ��������Ĵ��������Լ��Ļ�����Ѫ���Լ����Լ���
	if (weapon->getOwner() == this) return;
	//�ܵ������ȵ�Ѫ,��Ѫ����������������-���������
	addLifeValue(-weapon->getPower() / 10.0);

	// ���Ѫ��С��0��������
	if (getLifeValue() <= 0)
	{
		/* �����ɹ�ɱ������ */
		weapon->killCharacter(this);
		/* �������� */
		die();
	}
}

void Character::die()
{
	cout << this << " ������" << endl;
	if (isDie())return;
	_isDie = true;
}

void Character::update(float dt)
{
	if (detectionStatus())	// �����ǰ״������(�����Ƿ���)
	{
		move();
		/* ���ﱣ�ֲ���ת */
		//setRotation3D(Vec3::ZERO);
		//syncNodeToPhysics();
	}
}


bool Character::detectionStatus()
{
	if (!isDie() && getPositionY() < 0)		// ���������ҵ����˳���
	{
		cout << this << " ���������������" << endl;
		die();								// ������������
	}
	return !isDie();
}

void Character::createHpBar()
{
	auto billBoard = BillBoard::create();
	/* ������Ѫ���� */
	_hpSlider = Slider::create();
	_hpSlider->loadBarTexture("images/bloodbg.png");
	_hpSlider->loadProgressBarTexture("images/blood.png");
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setScale(.03f, .015f);
	_hpSlider->setPercent(_lifeValue);
	_hpSlider->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 2);
	billBoard->addChild(_hpSlider);

	/* ��������������label */
	TTFConfig ttfConfig("fonts/FZYTK.TTF", 25, GlyphCollection::DYNAMIC);
	_topName = Label::createWithTTF(ttfConfig, "");
	_topName->setScale(.02f);
	_topName->setTextColor(Color4B::BLACK);
	_topName->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 3);
	billBoard->addChild(_topName);
	addChild(billBoard);
}


Character::Attribute::Attribute()
{
	init();		// ֱ��ִ�г�ʼ������
}

Character::Attribute::~Attribute()
{

}

void Character::Attribute::addAttackDamage(const float &add)
{
	_attackDamage = max(0.0f, _attackDamage + add);
}

void Character::Attribute::addAttackSpeed(const float &add)
{
	_attackSpeed = max(0.0f, _attackSpeed + add);
}

void Character::Attribute::addMovingSpeed(const float &add)
{
	_movingSpeed = max(0.0f, _movingSpeed + add);
}

void Character::Attribute::addEmpiricalAcquisition(const float &add)
{
	_empiricalAcquisition = max(0.0f, _empiricalAcquisition + add);
}

void Character::Attribute::addDefensiveForce(const float &add)
{
	_defensiveForce = max(0.0f, _defensiveForce + add);
}

void Character::Attribute::addRestoringAbility(const float &add)
{
	_restoringAbility = max(0.0f, _restoringAbility + add);
}

void Character::Attribute::addView()
{
	_temporary |= kTemporaryView;
}

void Character::Attribute::addSmall()
{
	_temporary |= kTemporarySmall;
}

void Character::Attribute::addMagnet()
{
	_temporary |= kTemporaryMagnet;
}

void Character::Attribute::delView()
{
	_temporary &= ~kTemporaryView;
}

void Character::Attribute::delSmall()
{
	_temporary &= ~kTemporarySmall;
}

void Character::Attribute::delMagnet()
{
	_temporary &= ~kTemporaryMagnet;
}

void Character::Attribute::setDuration(float add)
{
	_duration = max(0.0f, _duration + add);
}

void Character::Attribute::init()
{
	_attackDamage = 1;
	_attackSpeed = 1;
	_movingSpeed = 20.f;
	_empiricalAcquisition = 1;
	_defensiveForce = 0;
	_restoringAbility = 1;
	_temporary = kTemporaryNone;
	_duration = 0;
}

void PlayerCharacter::initialization()
{
	// ��ִ�и���ĳ�ʼ������
	Character::initialization();
	// ���һ�����������ܻ��ظ���
	setName("Little Giant");
	setTopName(getName());
	// ����Ⱥ�䣬����Ϊ -1
	setDept(-1);
}

void PlayerCharacter::die()
{
	Character::die();

	switch (GameScene::getGameMode())
	{
	case kGameModeAdventure:			// ð��ģʽ
		GameScene::getDisplayManager()->showSorceBoard();
		cout << "������������Ϸ����~" << endl;
		break;
	case kGameModeTimer:				// ��ʱģʽ
		initialization();				// ��Ѫ����
		break;
	case kGameModeNight:				// ��ҹģʽ
		GameScene::getDisplayManager()->showSorceBoard();
		cout << "������������Ϸ����~" << endl;
		break;
	default:
		break;
	}
}

void PlayerCharacter::moveModule()
{
	getThreadMutex().lock();
	while (!isDie())
	{
		if (GameScene::getJoystick()->getReferenceCount() == 0 ||
			GameScene::getCamera()->getReferenceCount() == 0 ||
			getReferenceCount() == 0)
		{
			cout << "��⵽ĳ�����ѱ���������" << endl;
			break;
		}
		Vec3 res = Vec3::ZERO;
		if (GameScene::getJoystick()->getKeyW())
			res += Vec3(0, 0, -1);
		if (GameScene::getJoystick()->getKeyA())
			res += Vec3(-1, 0, 0);
		if (GameScene::getJoystick()->getKeyS())
			res += Vec3(0, 0, 1);
		if (GameScene::getJoystick()->getKeyD())
			res += Vec3(1, 0, 0);
		if (GameScene::getDisplayManager() != nullptr&&GameScene::getDisplayManager()->getRocker() != nullptr)
		{
			Vec2 dir = GameScene::getDisplayManager()->getRocker()->getDirection();
			res += Vec3(dir.x, 0, -dir.y);
		}
		setDirection(res.getNormalized());
		if (GameScene::getJoystick()->isFirstView())
		{
			/*Vec3 po;
			GameScene::getCamera()->getWorldToNodeTransform().getForwardVector(&po);
			cout << po.x << " " << po.y << " " << po.z << endl;*/
			GameScene::getCamera()->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 5);
		}
		else
		{
			GameScene::getCamera()->setPosition3D(getPosition3D() + Vec3(0, 50, 20));
		}
	}
	cout << "��������" << endl;
	getThreadMutex().unlock();
	cout << "���������ɹ�" << endl;
	cout << "����" << this << " �߳̽���" << endl;
}

EnemyCharacter::EnemyCharacter() :
	_aiMachine(new AIStateMachine(this))
{
}

void EnemyCharacter::initialization()
{
	// ��ִ�и���ĳ�ʼ������
	Character::initialization();
	// ���һ�����������ܻ��ظ���
	setName(CHARACTER_NAME[rand() % (sizeof(CHARACTER_NAME) / sizeof(string))]);
	setTopName(getName());
}

void EnemyCharacter::collisionWithStage()
{
	Character::collisionWithStage();	//���ø������ײ����
	int x = rand() % 3 - 1;
	int y = rand() % 3 - 1;
	setDirection(Vec3(x, 0, y));
}

void EnemyCharacter::die()
{
	Character::die();

	switch (GameScene::getGameMode())
	{
	case kGameModeAdventure:			// ð��ģʽ
		GameScene::getCharacterManager()->addToPool(this);
		break;
	case kGameModeTimer:				// ��ʱģʽ
		initialization();				// ��Ѫ����
		break;
	case kGameModeNight:				// ��ҹģʽ
		GameScene::getCharacterManager()->addToPool(this);
		break;
	default:
		break;
	}
}

void EnemyCharacter::moveModule()
{
	cout << this << " �߳�����" << endl;
	this_thread::sleep_for(chrono::milliseconds(2000));
	getThreadMutex().lock();
	while (!isDie())
	{
		if (GameScene::getCharacterManager()->getReferenceCount() == 0)
		{
			cout << "CharacterManager �ѱ�����������" << endl;
			break;
		}
		_aiMachine->run();
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	getThreadMutex().unlock();
	cout << "����" << this << " �߳̽���" << endl;
}

void EnemyCharacter::beAttacked(Weapons * const & weapon)
{
	Character::beAttacked(weapon);
	if (getLifeValue() < INITIAL_LIFE_VALUE / 4)	//��Ѫ��ת�Ƶ�Ѱ�ҽ���״̬
	{
		_aiMachine->changeState(AIStateMachine::kAIStateHPLess);
	}
	else											//ת�Ƶ�����״̬
	{
		_aiMachine->changeState(AIStateMachine::kAIStateBeAttack);
	}
}
