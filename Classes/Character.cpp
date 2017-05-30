#include "Character.h"
#include "Global.h"
#include "GameScene.h"
#include "3d/CCTerrain.h"
#include "3d/CCBundle3D.h"
#include "physics\CCPhysicsBody.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

USING_NS_CC;

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
	//CCLOG("start %f %f %f", getPosition3D().x, getPosition3D().y, getPosition3D().z);
	GameScene::getWeaponManager()->createWeapon(kWeaponArrow, this, getPosition3D(), pos);
}

void Character::die()
{

}

void Character::move(const Vec3 & pos)
{
	/* ����һ�������˶���~ */
	//auto s = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	//s->setLinearVelocity(s->getLinearVelocity() + pos);
	setPosition3D(getPosition3D() + pos);
}

bool Character::init()
{
	CCLOG("init");
	_hpSlider = Slider::create();
	_hpSlider->loadBarTexture("images/bloodbg.png");
	_hpSlider->loadProgressBarTexture("images/blood.png");
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setScale(.03f);
	_hpSlider->setPercent(_lifeValue / INITIAL_LIFE_VALUE * 100.0);
	_hpSlider->setRotation3D(Vec3(-90,0,0));
	_hpSlider->setPosition3D(getPosition3D()+Vec3::UNIT_Y*2);
	addChild(_hpSlider);
	return true;
}

Character * Character::create()
{
	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//�ݶ���������������Ϊ50
	des.shape = Physics3DShape::createBox(Vec3(2.0f, 2.0f, 2.0f));	//�����С
	auto character = new Character();
	if (character && character->initWithFile("Sprite3DTest/box.c3t") &&character->init())
	{
		auto obj = Physics3DRigidBody::create(&des);
		character->_physicsComponent = Physics3DComponent::create(obj);
		character->addComponent(character->_physicsComponent);
		character->_contentSize = character->getBoundingBox().size;
		character->setTexture("images/Icon.png");
		character->autorelease();

		obj->setCollisionCallback([&](const Physics3DCollisionInfo &ci) {
				if (!ci.collisionPointList.empty()) {
					if (ci.objB->getMask() != 0) {
						auto ps = PUParticleSystem3D::create("C:/Cocos/Cocos2d-x/cocos2d-x-3.10/tests/cpp-tests/Resources/Particle3D/scripts/mp_hit_04.pu");
						ps->setPosition3D(ci.collisionPointList[0].worldPositionOnB);
						ps->setScale(0.05f);
						ps->startParticleSystem();
						ps->setCameraMask(2);
						GameScene::getWeaponManager()->addChild(ps);
						ps->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]() {
							ps->removeFromParent();
						}), nullptr));
						ci.objB->setMask(0);
					}
					CCLOG("---------------- peng zhuang --------------------");
				}
			}
		);
		/* �����������ȷ�����λ�� */
		character->setPosition3D(Vec3(rand()%WORLD_LENGTH - WORLD_LENGTH/2, 100, rand()%WORLD_WIDTH - WORLD_WIDTH/2));

		character->setScale(2.f);
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
		//setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
	}
	else
	{
		static float attackTime = 0;
		attackTime += dt;
		if (attackTime > 10.f) {
			attack(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D());
			attackTime /= 10.f;
		}
		CCLOG("attack Time : %f", attackTime);
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
