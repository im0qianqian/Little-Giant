#include "Award.h"
#include "GameScene.h"
#include "Joystick.h"
#include "Global.h"

Award::Award():
	_isDeleted(true),
	_awardType(AwardType::kAwardEXP)
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
	randomType();

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

void Award::collisionWithCharacter(Character * const & character)
{
	// ��������Ѿ����˱��˾Ͳ����ٸ��ˣ�����Է������Ļ�Ҳ���ܱ��õ�
	if (isDeleted() || character->isDie())return;
	// ������������
	applyToCharacter(character);
	// ��������
	destroy();
}

void Award::applyToCharacter(Character * const & character)
{
	switch (_awardType)
	{
	case kAwardHP:
		character->addLifeValue(100.f);
		break;
	case kAwardEXP:
		character->addExperience(1.f);
		break;
	case kAwardSorce:
		character->addSorce(1.f);
		break;
	default:
		break;
	}
}

void Award::randomType()
{
	/* ���ȷ���������� */
	_awardType = AwardType(rand() % 3);
	switch (_awardType)
	{
	case kAwardEXP:
		setTexture("Sprite3DTest/brickwork_normal-map.jpg");
		break;
	case kAwardHP:
		setTexture("Sprite3DTest/brickwork-texture.jpg");
		break;
	case kAwardSorce:
		setTexture("Sprite3DTest/caustics.png");
		break;
	default:
		break;
	}
}
