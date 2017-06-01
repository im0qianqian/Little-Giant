#include "Weapons.h"
#include "Character.h"
#include "GameScene.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

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

void Weapons::update(float dt)
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
	Physics3DRigidBodyDes rbDes;										//����һ����ά�ռ����
	rbDes.originalTransform.translate(spos);							//����
	rbDes.mass = 1.f;													//���ø�������
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//�����С

	auto ret = new Arrow(owner, spos, epos);							//����һö��ʸ

	if (ret && ret->initWithFile("Sprite3DTest/box.c3t"))
	{
		auto obj = Physics3DRigidBody::create(&rbDes);
		ret->_physicsComponent = Physics3DComponent::create(obj);
		ret->addComponent(ret->_physicsComponent);
		ret->_contentSize = ret->getBoundingBox().size;
		ret->setTexture("images/Icon.png");
		ret->autorelease();
		
		obj->setCollisionCallback([&](const Physics3DCollisionInfo &ci) {
			if (!ci.collisionPointList.empty()) {
				if (ci.objA->getMask() != 0) {
					auto ps = PUParticleSystem3D::create("C:/Cocos/Cocos2d-x/cocos2d-x-3.10/tests/cpp-tests/Resources/Particle3D/scripts/mp_hit_04.pu");
					ps->setPosition3D(ci.collisionPointList[0].worldPositionOnB);
					ps->setScale(0.05f);
					ps->startParticleSystem();
					ps->setCameraMask((unsigned int)CameraFlag::USER1);
					GameScene::getWeaponManager()->addChild(ps);
					ps->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]() {
						ps->removeFromParent();
					}), nullptr));
					ci.objA->setMask(0);
				}
				CCLOG("---------------- peng zhuang --------------------");
			}
		}
		);
	}

	Vec3 linearVel = ret->getEpos() - ret->getSpos();					//���㹥�����������
	linearVel.y = 0;													//��ˮƽ������
	linearVel.normalize();												//��λ������
	ret->setPosition3D(ret->getSpos() + 2 * linearVel + Vec3::UNIT_Y);						//���ü�ʸ��ʼ������
	ret->setScale(0.5f);												//�������Ŵ�С
	linearVel *= ret->getSpeed();										//�ٶ�����
	auto rigidBody = static_cast<Physics3DRigidBody*>(ret->getPhysicsObj());
	rigidBody->setLinearFactor(Vec3::ONE);
	rigidBody->setLinearVelocity(linearVel);
	rigidBody->setAngularVelocity(Vec3::ZERO);
	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(0.4f);

	ret->syncNodeToPhysics();											//ͬ������������
	ret->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
	ret->setCameraMask((unsigned int)CameraFlag::USER1);
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
