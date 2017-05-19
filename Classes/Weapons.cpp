#include "Weapons.h"
#include "Character.h"

Weapons::Weapons()
{

}

Weapons::~Weapons()
{

}


bool Weapons::init(void *owner, float power, float speed, float distance, Vec3 spos, Vec3 epos)
{
	bool flag = false;
	do
	{
		_owner = owner;
		_power = power;
		_speed = speed;
		_distance = distance;
		_spos = spos;
		_epos = epos;
		attack();
		flag = true;
	} while (false);
	return flag;
}

void Arrow::attack()
{
	Physics3DRigidBodyDes rbDes;
	/* 计算攻击所在路线向量 */
	Vec3 linearVel = getEpos() - getSpos();

	/* 化为单位向量 */
	linearVel.normalize();
	/* 初始化初始速度 */
	linearVel *= getSpeed() + static_cast<Character*>(getOwner())->getAttribute().getAttackSpeed();
	CCLOG("Arrow attck: %g %g %g", linearVel.x, linearVel.y, linearVel.z);

	rbDes.originalTransform.translate(getSpos());
	rbDes.mass = 1.f;
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));
	auto sprite = PhysicsSprite3D::create("Sprite3DTest/box.c3t", &rbDes);
	sprite->setTexture("images/Icon.png");

	auto rigidBody = static_cast<Physics3DRigidBody*>(sprite->getPhysicsObj());
	rigidBody->setLinearFactor(Vec3::ONE);
	rigidBody->setLinearVelocity(linearVel);
	rigidBody->setAngularVelocity(Vec3::ZERO);
	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(0.4f);
	sprite->setPosition3D(getSpos());
	CCLOG("sPos %f %f %f", getSpos().x, getSpos().y, getSpos().z);
	sprite->setScale(0.5f);
	sprite->syncNodeToPhysics();
	sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE); //sync node to physics

	this->addChild(sprite);
	

	//optimize, only sync node to physics
}

void Bomb::attack()
{
	CCLOG("Bomb attck: %g %g", _position.x, _position.y);
}

void Dart::attack()
{
	CCLOG("Dart attck: %g %g", _position.x, _position.y);
}