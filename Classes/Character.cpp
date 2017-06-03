#include "Character.h"
#include "Global.h"
#include "GameScene.h"
#include "Joystick.h"

USING_NS_CC;

Character::Character() :
	_lifeValue(INITIAL_LIFE_VALUE),
	_experience(0),
	_sorce(0),
	_weaponType(kWeaponArrow),
	_isDie(true)
{
	// 设置属于人物标签
	setTag(kGlobalCharacter);
}

Character::~Character()
{
}

void Character::addLifeValue(const float &add)
{
	_lifeValue += add;
	_hpSlider->setPercent(_lifeValue);			//更新血量条
}

void Character::addExperience(const int &add)
{
	_experience += add;
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
		GameScene::getCharacterManager()->addCharacterToPool(this);
		//设置不可见
		setVisible(false);
		// 这里改变武器位置到 (0,-1,0) 这一点
		setPosition3D(-Vec3::UNIT_Y * 10);
		// 同步到物理世界
		syncNodeToPhysics();
	}
	else	//自己死亡
	{

	}
}

void Character::move(const Vec3 & pos)
{
	/* 上演一场滑冰运动吧~ */
	//auto s = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	//s->setLinearVelocity(s->getLinearVelocity() + pos);
	setPosition3D(getPosition3D() + pos);
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
	_hpSlider->setRotation3D(Vec3(-90,0,0));
	_hpSlider->setPosition3D(getPosition3D()+Vec3::UNIT_Y*2);
	addChild(_hpSlider);

	/* 以下是初始化部分 */
	initWithFile("Sprite3DTest/box.c3t");
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
	setVisible(false);	//设置不可见
	setPosition3D(-Vec3::UNIT_Y*10);	//设置初始坐标
	syncNodeToPhysics();
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

	setVisible(true);							//设置可见
	// 取出之后随机设置位置并同步
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2, 20, rand() % WORLD_WIDTH - WORLD_WIDTH / 2));
	syncNodeToPhysics();
}

void Character::beAttacked(const Weapons * weapon)
{
	addLifeValue(-weapon->getPower() / 1.0);	//受到攻击先掉血
	//cout << "life life -------------------------------> " << getLifeValue() << endl;

	// 如果血量小于0，则死亡
	if (getLifeValue() <= 0)
		die();
}

void Character::update(float dt)
{
	//CCLOG("update %f", dt);
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
		ret.normalize();
		move(ret*getAttribute().getMovingSpeed());
		GameScene::getCamera()->setPosition3D(GameScene::getCamera()->getPosition3D() + ret*getAttribute().getMovingSpeed());
		syncNodeToPhysics();
	}
	else if(!_isDie)
	{
		static float attackTime = 0;
		attackTime += dt;
		if (attackTime > 10.f) {
			attack(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D());
			attackTime /= 10.f;
		}
	}
}


Character::Attribute::Attribute() :
	_attackDamage(0),
	_attackRange(0),
	_attackSpeed(0),
	_movingSpeed(0.5f),
	_empiricalAcquisition(0),
	_defensiveForce(0),
	_restoringAbility(0),
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

void Character::Attribute::addAttackRange(const float &add)
{
	_attackRange = max(0.0f, _attackRange + add);
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
	_attackDamage = 0;
	_attackRange = 0;
	_attackSpeed = 0;
	_movingSpeed = .5f;
	_empiricalAcquisition = 0;
	_defensiveForce = 0;
	_restoringAbility = 0;
}
