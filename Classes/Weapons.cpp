#include "Weapons.h"
#include "Character.h"
#include "GameScene.h"
#include "Joystick.h"
#include "Global.h"

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
}

bool Weapons::init()
{
	bool flag = false;
	do
	{
		if (initWithFile("Sprite3DTest/box.c3t"))								//����������״
		{
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
			flag = true;
		}
	} while (false);
	return flag;
}

void Weapons::init(void * const & owner, const Vec3 & spos, const Vec3 & epos)
{
	// �������ò�������
	setOwner(owner);
	setSpos(spos);
	setEpos(epos);
	setPower(100.f * static_cast<Character*>(owner)->getAttribute().getAttackDamage());
	setSpeed(100.f * static_cast<Character*>(owner)->getAttribute().getAttackSpeed());
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

	syncNodeToPhysics();												//ͬ������������
}

void Weapons::killCharacter(Character * const &character) const
{
	// ����������
	auto *master = static_cast<Character*>(getOwner());
	// �õ��Է������о���ֵ��÷֣�BUG BUG BUG���������ȡ5�������
	master->addExperience(character->getExperience() + 10);
	// �õ��Է����еķ����������ȡ5��
	master->addSorce(character->getSorce() + 10);
	cout << master << " ɱ���� " << character << " ���õ�����ֵ��" << character->getExperience() << " ���õ�������" << character->getSorce() << endl;
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
	// ������ڳ��ϲ���û��ɾ��
	if (!isDeleted() && getPositionY() < 0)
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
