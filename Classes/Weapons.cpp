#include "Weapons.h"
#include "Character.h"
#include "GameScene.h"
#include "Joystick.h"
#include "Global.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

Weapons::Weapons() :
	_owner(nullptr),
	_power(0),
	_speed(0),
	_spos(Vec3::ZERO),
	_epos(Vec3::ZERO),
	_isDeleted(true)
{
	// 武器标签
	setTag(kGlobalWeapon);
}

Weapons::~Weapons()
{

}

/*
 * 因为武器对象在从父类图层中删除的时候写成 removeFromParent() 总是会出现内存冲突，
 * 所以先写成把武器对象移动到看不到的地方骗骗玩家的眼睛
 * 武器与地面等障碍物碰撞
 */

void Weapons::destroy()
{
	// 如果已经被删除则不需要重新添加
	if (_isDeleted)return;
	// 删除元素
	_isDeleted = true;
	// 添加到缓存池
	GameScene::getWeaponManager()->addToPool(this);
}

bool Weapons::init()
{
	initWithFile("Sprite3DTest/box.c3t");								//设置武器形状
	setTexture("images/Icon.png");										//设置材质

	Physics3DRigidBodyDes rbDes;										//定义一个三维空间刚体
	rbDes.mass = 1.f;													//设置刚体质量
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//刚体大小

	auto obj = Physics3DRigidBody::create(&rbDes);						//创建刚体对象

	_physicsComponent = Physics3DComponent::create(obj);				//利用该刚体对象创建组件

	addComponent(_physicsComponent);

	_contentSize = getBoundingBox().size;

	obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// 设置碰撞后的回调函数

	obj->setUserData(this);												// 设置用户数据为当前武器对象，碰撞检测中会使用

	setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);	//应用同步
	return true;
}

void Weapons::init(void * const & owner, const Vec3 & spos, const Vec3 & epos)
{
	// 首先设置部分属性
	setOwner(owner);
	setSpos(spos);
	setEpos(epos);
	setPower(100.f * static_cast<Character*>(owner)->getAttribute().getAttackDamage());
	setSpeed(100.f * static_cast<Character*>(owner)->getAttribute().getAttackSpeed());
	_isDeleted = false;

	Vec3 linearVel = getEpos() - getSpos();								//计算攻击方向的向量
	//linearVel.y = 0;													//沿水平方向打出
	linearVel.normalize();												//单位化向量
	Vec3 pos = getSpos() + 2 * linearVel + Vec3::UNIT_Y;				//武器起始坐标
	setPosition3D(pos);													//设置武器起始坐标
	setScale(0.5f);														//设置缩放大小
	linearVel *= getSpeed();											//速度向量

	auto obj = static_cast<Physics3DRigidBody*>(getPhysicsObj());		//获取刚体对象
	obj->setLinearVelocity(linearVel);									//设置线速度
	obj->setLinearFactor(Vec3::ONE);									//设置线性因子
	obj->setAngularVelocity(Vec3::ZERO);								//设置角速度
	obj->setCcdMotionThreshold(0.5f);									//设置运动阈值
	obj->setCcdSweptSphereRadius(0.4f);									//设置扫描球半径

	syncNodeToPhysics();												//同步至物理世界
}

void Weapons::killCharacter(Character * const &character) const
{
	// 武器的主人
	auto *master = static_cast<Character*>(getOwner());
	// 得到对方的所有经验值与得分（BUG BUG BUG），另外获取5个经验点
	master->addExperience(character->getExperience()+5);
	// 得到对方所有的分数，另外获取5分
	master->addSorce(character->getSorce()+5);
	cout << master << " 杀死了 " << character << " ，得到经验值：" << character->getExperience() << " ，得到分数：" << character->getSorce() << endl;
}

void Weapons::collisionWithStage()
{
	destroy();
}

void Weapons::collisionWithWeapon(Weapons * const & weapon)
{
	destroy();
}

void Weapons::collisionWithCharacter(Character * const & character)
{
	destroy();
}

void Weapons::update(float dt)
{
	// 如果不在场上并且没有删除
	if (getPositionY() < 0 && !isDeleted())
	{
		destroy();
	}
}

Arrow::Arrow(void * owner, Vec3 spos, Vec3 epos)
{
}

Arrow::~Arrow()
{
}

Arrow *Arrow::create(void *owner, Vec3 spos, Vec3 epos)
{
	return nullptr;
}

Bomb::Bomb(void * owner, Vec3 spos, Vec3 epos)
{
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
}

Dart::~Dart()
{
}

Dart * Dart::create(void * owner, Vec3 spos, Vec3 epos)
{
	return nullptr;
}
