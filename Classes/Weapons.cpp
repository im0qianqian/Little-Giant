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
	// ������ǩ
	setTag(kGlobalWeapon);
}

Weapons::~Weapons()
{

}

/*
 * ��Ϊ���������ڴӸ���ͼ����ɾ����ʱ��д�� removeFromParent() ���ǻ�����ڴ��ͻ��
 * ������д�ɰ����������ƶ����������ĵط�ƭƭ��ҵ��۾�
 * �����������ϰ�����ײ
 */

void Weapons::destroy()
{
	// ����Ѿ���ɾ������Ҫ�������
	if (_isDeleted)return;
	// ɾ��Ԫ��
	_isDeleted = true;
	// ��ӵ������
	GameScene::getWeaponManager()->addToPool(this);
	// ���ò��ɼ�
	setVisible(false);
	// ����ı�����λ�õ� (0,-10,0) ��һ��
	setPosition3D(-Vec3::UNIT_Y * 10);
	// ͬ������������
	syncNodeToPhysics();
}

bool Weapons::init()
{
	initWithFile("Sprite3DTest/box.c3t");								//����������״
	setTexture("images/Icon.png");										//���ò���

	Physics3DRigidBodyDes rbDes;										//����һ����ά�ռ����
	rbDes.mass = 1.f;													//���ø�������
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//�����С

	auto obj = Physics3DRigidBody::create(&rbDes);						//�����������

	_physicsComponent = Physics3DComponent::create(obj);				//���øø�����󴴽����

	addComponent(_physicsComponent);

	_contentSize = getBoundingBox().size;

	obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// ������ײ��Ļص�����

	obj->setUserData(this);												// �����û�����Ϊ��ǰ����������ײ����л�ʹ��

	setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);	//Ӧ��ͬ��

	setVisible(false);
	setPosition3D(-Vec3::UNIT_Y*10);
	// ͬ������������
	syncNodeToPhysics();
	return true;
}

void Weapons::init(void * const & owner, const Vec3 & spos, const Vec3 & epos)
{
	// �������ò�������
	setOwner(owner);
	setSpos(spos);
	setEpos(epos);
	setPower(100.f + static_cast<Character*>(owner)->getAttribute().getAttackDamage());
	setSpeed(100.f + static_cast<Character*>(owner)->getAttribute().getAttackSpeed());
	_isDeleted = false;

	Vec3 linearVel = getEpos() - getSpos();								//���㹥�����������
	//linearVel.y = 0;													//��ˮƽ������
	linearVel.normalize();												//��λ������
	Vec3 pos = getSpos() + 2 * linearVel + Vec3::UNIT_Y;				//������ʼ����
	setPosition3D(pos);													//����������ʼ����
	setScale(0.5f);														//�������Ŵ�С
	linearVel *= getSpeed();											//�ٶ�����

	auto obj = static_cast<Physics3DRigidBody*>(getPhysicsObj());		//��ȡ�������
	obj->setLinearVelocity(linearVel);									//�������ٶ�
	obj->setLinearFactor(Vec3::ONE);									//������������
	obj->setAngularVelocity(Vec3::ZERO);								//���ý��ٶ�
	obj->setCcdMotionThreshold(0.5f);									//�����˶���ֵ
	obj->setCcdSweptSphereRadius(0.4f);									//����ɨ����뾶

	setVisible(true);
	syncNodeToPhysics();												//ͬ������������
}

void Weapons::update(float dt)
{
	// ������ڳ��ϲ���û��ɾ��
	if (getPositionY() < 0 && !_isDeleted)
	{
		destroy();
	}
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
	return nullptr;
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
