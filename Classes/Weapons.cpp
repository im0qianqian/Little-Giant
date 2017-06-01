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
	// 武器标签
	setTag(kGlobalWeapon);
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
	Physics3DRigidBodyDes rbDes;										//定义一个三维空间刚体
	rbDes.originalTransform.translate(spos);							//坐标
	rbDes.mass = 1.f;													//设置刚体质量
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//刚体大小

	auto ret = new Arrow(owner, spos, epos);							//创建一枚箭矢
	CCLOG("arrow ads: %d", ret);

	if (ret && ret->initWithFile("Sprite3DTest/box.c3t"))
	{
		auto obj = Physics3DRigidBody::create(&rbDes);

		// 设置用户数据为武器对象，碰撞检测中会使用
		obj->setUserData(ret);

		ret->_physicsComponent = Physics3DComponent::create(obj);
		ret->addComponent(ret->_physicsComponent);
		ret->_contentSize = ret->getBoundingBox().size;
		ret->setTexture("images/Icon.png");
		ret->autorelease();

		obj->setCollisionCallback([&](const Physics3DCollisionInfo &ci) {
			if (!ci.collisionPointList.empty()) {
				if (ci.objA->getMask() != 0) {
					/* 武器碰撞粒子特效 */
					auto ps = PUParticleSystem3D::create("C:/Cocos/Cocos2d-x/cocos2d-x-3.10/tests/cpp-tests/Resources/Particle3D/scripts/mp_hit_04.pu");
					ps->setPosition3D(ci.collisionPointList[0].worldPositionOnB);
					ps->setScale(0.05f);
					ps->startParticleSystem();
					ps->setCameraMask((unsigned int)CameraFlag::USER1);
					GameScene::getWeaponManager()->addChild(ps);
					ps->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]() {
						ps->removeFromParent();
					}), nullptr));

					/* 获取两个碰撞对象 */
					auto *objA = static_cast<Node*>(ci.objA->getUserData());
					auto *objB = static_cast<Node*>(ci.objB->getUserData());
					CCASSERT(objA, "OBJ A NULL");
					CCASSERT(objB, "OBJ B NULL");
					if (objA != NULL && objB != NULL)
					{
						CCLOG("---------------- weapon stage --------------------");
						CCLOG("tag aa : %d", objA->Node::getTag());
						CCLOG("tag bb : %d", objB->Node::getTag());
						/*
						 * 因为武器对象在从父类图层中删除的时候写成 removeFromParent() 总是会出现内存冲突，
						 * 所以先写成把武器对象移动到看不到的地方骗骗玩家的眼睛
						 */
						if (gObjectEqual(objA->Node::getTag(), objB->Node::getTag(), kGlobalWeapon, kGlobalStage))
						{
							Weapons *weapon;
							if (objA->Node::getTag() == kGlobalWeapon)
							{
								weapon = dynamic_cast<Weapons*>(objA);
							}
							else if(objB->Node::getTag() == kGlobalWeapon)
							{
								weapon = dynamic_cast<Weapons*>(objB);
							}
							// 这里改变武器位置到 (0,-100,0) 这一点
							weapon->setPosition3D(-Vec3::UNIT_Y * 100);
							// 同步到物理世界
							weapon->syncNodeToPhysics();
						}
					}
					ci.objA->setMask(0);
				}
			}
		});

		Vec3 linearVel = ret->getEpos() - ret->getSpos();					//计算攻击方向的向量
		linearVel.y = 0;													//沿水平方向打出
		linearVel.normalize();												//单位化向量
		ret->setPosition3D(ret->getSpos() + 2 * linearVel + Vec3::UNIT_Y);						//设置箭矢起始点坐标
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
		ret->setCameraMask((unsigned int)CameraFlag::USER1);

	}
	else
	{
		delete ret;
		ret = nullptr;
	}
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
