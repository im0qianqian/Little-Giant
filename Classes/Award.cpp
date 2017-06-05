#include "Award.h"
#include "GameScene.h"
#include "Joystick.h"

Award::Award():
	_isDeleted(true)
{
	// ������ǩ
	setTag(kGlobalAward);
}

Award::~Award()
{
}

bool Award::init()
{
	initWithFile("Sprite3DTest/box.c3t");								//������״
	setTexture("Sprite3DTest/teapot.png");								//���ò���

	Physics3DRigidBodyDes rbDes;										//����һ����ά�ռ����
	rbDes.mass = 0.f;													//���ø�������
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//�����С

	auto obj = Physics3DRigidBody::create(&rbDes);						//�����������

	_physicsComponent = Physics3DComponent::create(obj);				//���øø�����󴴽����

	addComponent(_physicsComponent);

	_contentSize = getBoundingBox().size;

	obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// ������ײ��Ļص�����

	obj->setUserData(this);

	setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);	//Ӧ��ͬ��
	return true;
}

void Award::initialization()
{
	_isDeleted = false;
	
	// ȡ��֮���������λ�ò�ͬ��
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2, 0, rand() % WORLD_WIDTH - WORLD_WIDTH / 2)+Vec3::UNIT_Y);

	syncNodeToPhysics();
}

void Award::destroy()
{
	// ����Ѿ���ɾ������Ҫ�������
	if (_isDeleted)return;
	// ɾ��Ԫ��
	_isDeleted = true;
	// ��ӵ������
	GameScene::getAwardManager()->addToPool(this);
}
