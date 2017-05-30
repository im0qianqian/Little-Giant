#include "Character.h"
#include "Global.h"
#include "GameScene.h"
#include "Joystick.h"

Character::Character() :
	_lifeValue(INITIAL_LIFE_VALUE),
	_experience(0),
	_sorce(0),
	_weaponType(kWeaponArrow),
	_isDie(false)
{
}

Character::~Character()
{
}

void Character::addLifeValue(float add)
{
	_lifeValue += add;
}

void Character::addExperience(int add)
{
	_experience += add;
}

void Character::addSorce(int add)
{
	_sorce += add;
}

void Character::attack(const Vec3 &pos)
{
	CCLOG("Attack success! %f %f %f", pos.x, pos.y, pos.z);
	CCLOG("start %f %f %f", getPosition3D().x, getPosition3D().y, getPosition3D().z);
	GameScene::getWeaponManager()->createWeapon(kWeaponArrow, this, getPosition3D(), pos);
}

void Character::die()
{

}

void Character::move(const Vec3 & pos)
{
	auto a = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	a->setLinearVelocity(a->getLinearVelocity()+pos);
	//setPosition3D(getPosition3D() + pos);
}

bool Character::init()
{
	CCLOG("init");
	return true;
}

Character * Character::create()
{
	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//暂定，人物质量设置为50
	des.shape = Physics3DShape::createBox(Vec3(2.0f, 4.0f, 2.0f));	//刚体大小
	auto character = new Character();
	
	if (character && character->initWithFile("images/orc.c3b"))
	{
		auto obj = Physics3DRigidBody::create(&des);
		character->_physicsComponent = Physics3DComponent::create(obj);
		character->addComponent(character->_physicsComponent);
		character->_contentSize = character->getBoundingBox().size;
		//character->setTexture("images/Icon.png");
		character->autorelease();
		character->setPosition3D(Vec3(0, 100, 0));
		character->setScale(.3f);
		character->syncNodeToPhysics();
		character->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
		character->setCameraMask((unsigned int)CameraFlag::USER1);
	}
	else
	{
		delete character;
		character = nullptr;
	}
	return character;
}

void Character::update(float dt)
{
	CCLOG("update %f", dt);
	Vec3 ret = Vec3::ZERO;
	if (Joystick::getKeyW())
		ret += Vec3(0, 0, -1);
	if (Joystick::getKeyA())
		ret += Vec3(-1, 0, 0);
	if (Joystick::getKeyS())
		ret += Vec3(0, 0, 1);
	if (Joystick::getKeyD())
		ret += Vec3(1, 0, 0);
	move(ret*getAttribute().getMovingSpeed());
	GameScene::getCamera()->setPosition3D(GameScene::getCamera()->getPosition3D()+ret*getAttribute().getMovingSpeed());
	GameScene::getCamera()->lookAt(getPosition3D());
	syncNodeToPhysics();
	setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
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

void Character::Attribute::addAttackDamage(float add)
{
	_attackDamage = max(0.0f, _attackDamage + add);
}

void Character::Attribute::addAttackRange(float add)
{
	_attackRange = max(0.0f, _attackRange + add);
}

void Character::Attribute::addAttackSpeed(float add)
{
	_attackSpeed = max(0.0f, _attackSpeed + add);
}

void Character::Attribute::addMovingSpeed(float add)
{
	_movingSpeed = max(0.0f, _movingSpeed + add);
}

void Character::Attribute::addEmpiricalAcquisition(float add)
{
	_empiricalAcquisition = max(0.0f, _empiricalAcquisition + add);
}

void Character::Attribute::addDefensiveForce(float add)
{
	_defensiveForce = max(0.0f, _defensiveForce + add);
}

void Character::Attribute::addRestoringAbility(float add)
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
