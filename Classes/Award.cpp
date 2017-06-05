#include "Award.h"
#include "GameScene.h"
#include "Joystick.h"

Award::Award():
	_isDeleted(true)
{
	// 武器标签
	setTag(kGlobalAward);
}

Award::~Award()
{
}

bool Award::init()
{
	initWithFile("Sprite3DTest/box.c3t");								//设置形状
	setTexture("Sprite3DTest/teapot.png");								//设置材质

	Physics3DRigidBodyDes rbDes;										//定义一个三维空间刚体
	rbDes.mass = 0.f;													//设置刚体质量
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//刚体大小

	auto obj = Physics3DRigidBody::create(&rbDes);						//创建刚体对象

	_physicsComponent = Physics3DComponent::create(obj);				//利用该刚体对象创建组件

	addComponent(_physicsComponent);

	_contentSize = getBoundingBox().size;

	obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// 设置碰撞后的回调函数

	obj->setUserData(this);

	setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);	//应用同步
	return true;
}

void Award::initialization()
{
	_isDeleted = false;
	
	// 取出之后随机设置位置并同步
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2, 0, rand() % WORLD_WIDTH - WORLD_WIDTH / 2)+Vec3::UNIT_Y);

	syncNodeToPhysics();
}

void Award::destroy()
{
	// 如果已经被删除则不需要重新添加
	if (_isDeleted)return;
	// 删除元素
	_isDeleted = true;
	// 添加到缓存池
	GameScene::getAwardManager()->addToPool(this);
}
