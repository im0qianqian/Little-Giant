#include "Weapons.h"
#include "Character.h"

Weapons::Weapons() :
	_owner(nullptr),
	_power(0),
	_speed(0),
	_spos(Vec3::ZERO),
	_epos(Vec3::ZERO)
{

}

Weapons::~Weapons()
{

}


Arrow::Arrow(void * owner, Vec3 spos, Vec3 epos)
{
	setOwner(owner);
	setSpos(spos);
	setEpos(epos);
	setPower(100.f + static_cast<Character*>(owner)->getAttribute().getAttackDamage());
	setSpeed(100.f + static_cast<Character*>(owner)->getAttribute().getAttackSpeed());
}

Arrow::~Arrow()
{
}

Arrow *Arrow::create(void *owner, Vec3 spos, Vec3 epos)
{
	Physics3DRigidBodyDes rbDes;										//定义一个三维空间刚体
	rbDes.originalTransform.translate(spos);							//坐标
	rbDes.mass = 1.f;													//设置刚体质量
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//刚体大小

	auto ret = new Arrow(owner, spos, epos);							//创建一枚箭矢

	if (ret && ret->initWithFile("Sprite3DTest/box.c3t"))
	{
		auto obj = Physics3DRigidBody::create(&rbDes);
		ret->_physicsComponent = Physics3DComponent::create(obj);
		ret->addComponent(ret->_physicsComponent);
		ret->_contentSize = ret->getBoundingBox().size;
		ret->setTexture("images/Icon.png");
		ret->autorelease();
	}

	Vec3 linearVel = ret->getEpos() - ret->getSpos();					//计算攻击方向的向量
	linearVel.y = 0;													//沿水平方向打出
	linearVel.normalize();												//单位化向量
	ret->setPosition3D(ret->getSpos() + linearVel);						//设置箭矢起始点坐标
	ret->setScale(0.5f);												//设置缩放大小
	linearVel *= ret->getSpeed();										//速度向量
	auto rigidBody = static_cast<Physics3DRigidBody*>(ret->getPhysicsObj());
	rigidBody->setLinearFactor(Vec3::ONE);
	rigidBody->setLinearVelocity(linearVel);
	rigidBody->setAngularVelocity(Vec3::ZERO);
	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(0.4f);
	
	ret->syncNodeToPhysics();											//同步至物理世界
	ret->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);

	CCLOG("attack success!!!");
	return ret;
}

Bomb::Bomb(void * owner, Vec3 spos, Vec3 epos)
{
	setOwner(owner);
	setSpos(spos);
	setEpos(epos);
	setPower(200.f + static_cast<Character*>(owner)->getAttribute().getAttackDamage());
	setSpeed(50.f + static_cast<Character*>(owner)->getAttribute().getAttackSpeed());
}

Bomb::~Bomb()
{
}

Bomb * Bomb::create(void * owner, Vec3 spos, Vec3 epos)
{
	return nullptr;
}

Dart::Dart(void * owner, Vec3 spos, Vec3 epos)
{
	setOwner(owner);
	setSpos(spos);
	setEpos(epos);
	setPower(150.f + static_cast<Character*>(owner)->getAttribute().getAttackDamage());
	setSpeed(70.f + static_cast<Character*>(owner)->getAttribute().getAttackSpeed());
}

Dart::~Dart()
{
}

Dart * Dart::create(void * owner, Vec3 spos, Vec3 epos)
{
	return nullptr;
}
