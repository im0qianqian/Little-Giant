#include "Character.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Joystick.h"
#include "Weapons.h"
#include "Award.h"
#include "WeaponManager.h"
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
	// 设置属于人物标签
	setTag(kGlobalCharacter);
}

Character::~Character()
{
	// 设置死亡
	_isDie = true;
	// 加锁等待线程结束
	cout << this << " clean up 加锁" << endl;
	_threadMutex.lock();
	cout << this << " clean up 加锁成功~" << endl;
	cout << this << " clean up 解锁" << endl;
	_threadMutex.unlock();
	cout << this << " clean up 解锁成功~" << endl;
	cout << this << " 已被析构" << endl;
	cout << "----------------------" << endl;
}

void Character::addLifeValue(const float &add)
{
	if (add >= 0)
	{
		// 加血时增加恢复能力加成
		_lifeValue += min(INITIAL_LIFE_VALUE, add*getAttribute().getRestoringAbility());
	}
	else
	{
		// 减血时减掉防御力所抵消的伤害
		_lifeValue += min(add + getAttribute().getDefensiveForce(), 0);
	}
	_hpSlider->setPercent(_lifeValue);			//更新血量条
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
	const float attackTimeInterval = 600.f / getAttribute().getAttackSpeed();		// 攻击时间间隔
	int currentTime = GetCurrentTime();												// 获取当前时间
	if (currentTime - _lastAttackTime >= attackTimeInterval)						//如果可以攻击
	{
		_lastAttackTime = currentTime;												// 更新最后一次攻击时间
		GameScene::getWeaponManager()->createWeapon(kWeaponArrow, this, getPosition3D(), pos);
	}
}

void Character::move()
{
	/* 获取刚体对象 */
	auto s = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	/* 设置线速度为人物移动速度*方向向量，Y方向保持和原来一样 */
	s->setLinearVelocity(getAttribute().getMovingSpeed()*getDirection() + Vec3(0, s->getLinearVelocity().y, 0));
}

bool Character::init()
{
	bool flag = false;
	do
	{
		/* 以下是初始化部分 */
		if (initWithFile("Sprite3DTest/box.c3t"))
		{
			setTexture("images/Icon.png");

			Physics3DRigidBodyDes des;
			des.mass = 50.f;			//暂定，人物质量设置为50
			des.shape = Physics3DShape::createBox(Vec3(2.0f, 2.0f, 2.0f));	//刚体大小

			auto obj = Physics3DRigidBody::create(&des);

			_physicsComponent = Physics3DComponent::create(obj);

			addComponent(_physicsComponent);

			_contentSize = getBoundingBox().size;

			obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// 设置碰撞后的回调函数

			obj->setUserData(this);

			setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);	//应用同步

			setScale(2.f);		//设置大小
			createHpBar();		//创建血量条

			flag = true;
		}
	} while (false);
	return flag;
}

void Character::initialization()
{
	// 初始化值
	_lifeValue = INITIAL_LIFE_VALUE;
	_experience = 0;
	// 如果不是计时模式，积分清空
	if(GameScene::getGameMode()!=kGameModeTimer)
		_sorce = 0;
	_attribute.init();
	_weaponType = kWeaponArrow;
	_dept = 0;
	_hpSlider->setPercent(_lifeValue);		//更新血量条
	_lastAttackTime = 0;					//攻击时间间隔
	_direction = Vec3::ZERO;				//初始行走方向
	
	thread([this] {							//异步更新 isDie 加锁并且启动人物AI线程
		_threadMutex.lock();
		_isDie = false;						//复活
		thread(&Character::moveModule, this).detach();	//开启人物AI线程
		_threadMutex.unlock();
	}).detach();
	

	// 随机设置位置并同步
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2.0, WORLD_HEIGHT, rand() % WORLD_WIDTH - WORLD_WIDTH / 2.0));
	syncNodeToPhysics();
}

void Character::collisionWithWeapon(Weapons * const & weapon)
{
	if (isDie() || weapon->isDeleted())return;	// 如果某方已经不存在
	// 人物受到攻击
	beAttacked(weapon);
	//cout << this << " 受到来自 " << weapon << " 的攻击！！！" << endl;
}

void Character::collisionWithAward(Award * const & award)
{
	[this]()
	{
		auto rootps = PUParticleSystem3D::create("images/blackHole.pu", "C:/Cocos/Cocos2d-x/cocos2d-x-3.10/tests/cpp-tests/Resources/Particle3D/materials/pu_mediapack_01.material");
		rootps->setCameraMask((short int)CameraFlag::USER1);
		rootps->setPosition3D(getPosition3D());
		rootps->setScale(.1f);
		GameScene::getCharacterManager()->addChild(rootps);
		rootps->runAction(Sequence::create(CCFadeIn::create(.5f), CCDelayTime::create(1.f), CCFadeOut::create(.5f), CallFunc::create([=]() {
			rootps->removeFromParent();
		}), nullptr));
		rootps->startParticleSystem();
	}();
}

void Character::beAttacked(Weapons *const &weapon)
{
	// 如果武器的创建者是自己的话不掉血（自己打自己）
	if (weapon->getOwner() == this) return;
	//受到攻击先掉血,掉血量等于武器攻击力-自身防御力
	addLifeValue(-weapon->getPower() / 10.0);

	// 如果血量小于0，则死亡
	if (getLifeValue() <= 0)
	{
		/* 武器成功杀死敌人 */
		weapon->killCharacter(this);
		/* 自身死亡 */
		die();
	}
}

void Character::die()
{
	cout << this << " 已死亡" << endl;
	if (isDie())return;
	_isDie = true;
}

void Character::update(float dt)
{
	if (detectionStatus())	// 如果当前状况正常(人物是否存活)
	{
		move();
		/* 人物保持不旋转 */
		//setRotation3D(Vec3::ZERO);
		//syncNodeToPhysics();
	}
}


bool Character::detectionStatus()
{
	if (!isDie() && getPositionY() < 0)		// 如果人物存活并且掉出了场外
	{
		cout << this << " 人物掉出世界死亡" << endl;
		die();								// 人物立即死亡
	}
	return !isDie();
}

void Character::createHpBar()
{
	auto billBoard = BillBoard::create();
	/* 以下是血量条 */
	_hpSlider = Slider::create();
	_hpSlider->loadBarTexture("images/bloodbg.png");
	_hpSlider->loadProgressBarTexture("images/blood.png");
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setScale(.03f, .015f);
	_hpSlider->setPercent(_lifeValue);
	_hpSlider->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 2);
	billBoard->addChild(_hpSlider);

	/* 以下是人物名字label */
	TTFConfig ttfConfig("fonts/FZYTK.TTF", 25, GlyphCollection::DYNAMIC);
	_topName = Label::createWithTTF(ttfConfig,"");
	_topName->setScale(.02f);
	_topName->setTextColor(Color4B::BLACK);
	_topName->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 3);
	billBoard->addChild(_topName);
	addChild(billBoard);
}


Character::Attribute::Attribute()
{
	init();		// 直接执行初始化函数
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
	// 先执行父类的初始化方法
	Character::initialization();
	// 随机一个姓名（可能会重复）
	setName("Little Giant");
	setTopName(getName());
	// 设置群落，主角为 -1
	setDept(-1);
}

void PlayerCharacter::die()
{
	Character::die();

	switch (GameScene::getGameMode())
	{
	case kGameModeAdventure:			// 冒险模式
		GameScene::getDisplayManager()->showSorceBoard();
		cout << "你已死亡，游戏结束~" << endl;
		break;
	case kGameModeTimer:				// 计时模式
		initialization();				// 充血复活
		break;
	case kGameModeNight:				// 黑夜模式
		GameScene::getDisplayManager()->showSorceBoard();
		cout << "你已死亡，游戏结束~" << endl;
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
		Vec3 res = Vec3::ZERO;
		if (GameScene::getJoystick()->getKeyW())
			res += Vec3(0, 0, -1);
		if (GameScene::getJoystick()->getKeyA())
			res += Vec3(-1, 0, 0);
		if (GameScene::getJoystick()->getKeyS())
			res += Vec3(0, 0, 1);
		if (GameScene::getJoystick()->getKeyD())
			res += Vec3(1, 0, 0);
		setDirection(res.getNormalized());
		if (GameScene::getJoystick()->isFirstView())
		{
			GameScene::getCamera()->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 5);
		}
		else
		{
			GameScene::getCamera()->setPosition3D(getPosition3D() + Vec3(0, 50, 20));
			//GameScene::getCamera()->lookAt(getPosition3D());
			//GameScene::getCamera()->setPosition3D(GameScene::getCamera()->getPosition3D()+ .7*ret.getNormalized());
		}
	}
	cout << "死亡解锁" << endl;
	getThreadMutex().unlock();
	cout << "死亡解锁成功" << endl;
	cout << "主角" <<this<< " 线程结束" << endl;
}

void EnemyCharacter::initialization()
{
	// 先执行父类的初始化方法
	Character::initialization();
	// 随机一个姓名（可能会重复）
	setName(CHARACTER_NAME[rand() % (sizeof(CHARACTER_NAME) / sizeof(string))]);
	setTopName(getName());
}

void EnemyCharacter::die()
{
	Character::die();

	switch (GameScene::getGameMode())
	{
	case kGameModeAdventure:			// 冒险模式
		GameScene::getCharacterManager()->addToPool(this);
		break;
	case kGameModeTimer:				// 计时模式
		initialization();				// 充血复活
		break;
	case kGameModeNight:				// 黑夜模式
		GameScene::getCharacterManager()->addToPool(this);
		break;
	default:
		break;
	}
}

void EnemyCharacter::moveModule()
{
	cout << this << " 线程启动" << endl;
	getThreadMutex().lock();
	while (!isDie())
	{
		if (GameScene::getCharacterManager() == nullptr || GameScene::getCharacterManager()->getPlayerCharacter() == nullptr)continue;
		Vec3 minn = Vec3::ZERO;
		minn = GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() - getPosition3D();
		auto other = GameScene::getCharacterManager()->getEnemyCharacter();

		int len = other.size();
		for (std::set<Character*>::iterator i = other.begin(); i != other.end(); i++)
		{
			if (*i != this && ((*i)->getPosition3D() - getPosition3D()).length() < minn.length())
			{
				minn = (*i)->getPosition3D() - getPosition3D();
			}
		}
		minn.y = 0;
		if (minn.length() < 20.0)
		{
			attack(minn + getPosition3D());
			setDirection(minn.getNormalized());
			if (minn.length() < 10.0)
			{
				setDirection(Vec3::ZERO);
			}
		}
		else
		{
			setDirection(minn.getNormalized());
		}
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	getThreadMutex().unlock();
	cout << "敌人" << this << " 线程结束" << endl;
}
