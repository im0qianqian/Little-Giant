#include "Character.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Joystick.h"
#include "Weapons.h"

USING_NS_CC;

Character::Character() :
	_dept(0),
	_lifeValue(INITIAL_LIFE_VALUE),
	_experience(0),
	_sorce(0),
	_weaponType(kWeaponArrow),
	_isDie(true),
	_attribute(Attribute()),
	_hpSlider(nullptr)
{
	// 设置属于人物标签
	setTag(kGlobalCharacter);
}

Character::~Character()
{
}

void Character::addLifeValue(const float &add)
{
	if (add >= 0)
	{
		// 加血时增加恢复能力加成
		_lifeValue += add*getAttribute().getRestoringAbility();
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
	cout << "当前经验值：" << _experience << endl;
}

void Character::addSorce(const int &add)
{
	_sorce += add;
}

void Character::attack(const Vec3 &pos)
{
	//CCLOG("Attack success! %f %f %f", pos.x, pos.y, pos.z);
	//CCLOG("start %f %f %f", getPosition3D().x, getPosition3D().y, getPosition3D().z);
	GameScene::getWeaponManager()->createWeapon(kWeaponArrow, this, getPosition3D(), pos);
}

void Character::die()
{
	if (_isDie)return;
	_isDie = true;
	if (getDept() != -1)	// 其他人物死亡
	{
		GameScene::getCharacterManager()->addToPool(this);
	}
	else	//自己死亡
	{

	}
}

void Character::move(const Vec3 & pos)
{
	/* 获取刚体对象 */
	auto s = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	/* 设置线速度为人物移动速度*方向向量，Y方向保持和原来一样 */
	s->setLinearVelocity(getAttribute().getMovingSpeed()*pos + Vec3(0, s->getLinearVelocity().y, 0));
}

bool Character::init()
{
	/* 以下是血量条 */
	_hpSlider = Slider::create();
	_hpSlider->loadBarTexture("images/bloodbg.png");
	_hpSlider->loadProgressBarTexture("images/blood.png");
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setScale(.03f);
	_hpSlider->setPercent(_lifeValue);
	_hpSlider->setRotation3D(Vec3(-90, 0, 0));
	_hpSlider->setPosition3D(getPosition3D() + Vec3::UNIT_Y * 2);
	addChild(_hpSlider);

	/* 以下是初始化部分 */
	initWithFile("Sprite3DTest/box.c3t");
	//initWithFile("Sprite3DTest/sphere.c3b");
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
	return true;
}

void Character::initialization()
{
	// 初始化值
	_lifeValue = INITIAL_LIFE_VALUE;
	_experience = 0;
	_sorce = 0;
	_attribute.init();
	_weaponType = kWeaponArrow;
	_isDie = false;
	_hpSlider->setPercent(_lifeValue);			//更新血量条
	_dept = 0;

	// 取出之后随机设置位置并同步
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2, 20, rand() % WORLD_WIDTH - WORLD_WIDTH / 2));

	syncNodeToPhysics();
}

void Character::collisionWithWeapon(Weapons * const & weapon)
{
	// 人物受到攻击
	beAttacked(weapon);
	cout << this << " 受到来自 " << weapon << " 的攻击！！！" << endl;
}

void Character::beAttacked(Weapons *const &weapon)
{
	//受到攻击先掉血,掉血量等于武器攻击力-自身防御力
	addLifeValue(-weapon->getPower() / 1.0);

	// 如果血量小于0，则死亡
	if (getLifeValue() <= 0)
	{
		/* 武器成功杀死敌人 */
		weapon->killCharacter(this);
		/* 自身死亡 */
		die();
	}
}

void Character::update(float dt)
{
	if (_dept == -1)
	{
		Vec3 ret = Vec3::ZERO;
		if (GameScene::getJoystick()->getKeyW())
			ret += Vec3(0, 0, -1);
		if (GameScene::getJoystick()->getKeyA())
			ret += Vec3(-1, 0, 0);
		if (GameScene::getJoystick()->getKeyS())
			ret += Vec3(0, 0, 1);
		if (GameScene::getJoystick()->getKeyD())
			ret += Vec3(1, 0, 0);
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
		move(ret.getNormalized());
		syncNodeToPhysics();
	}
	else if (!_isDie)
	{
		static float attackTime = 0;
		attackTime += dt;
		static Vec3 minn = Vec3::ZERO;
		if (attackTime > 10.f) {
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
			attack(minn);
			move(minn.getNormalized());
			attackTime /= 10.f;
		}
	}
}


Character::Attribute::Attribute() :
	_attackDamage(1),
	_attackSpeed(1),
	_movingSpeed(50.f),
	_empiricalAcquisition(1),
	_defensiveForce(0),
	_restoringAbility(1),
	_temporary(kTemporaryNone),
	_duration(0)
{

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
	_movingSpeed = 50.f;
	_empiricalAcquisition = 1;
	_defensiveForce = 0;
	_restoringAbility = 1;
	_temporary = kTemporaryNone;
	_duration = 0;
}
