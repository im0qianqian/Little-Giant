#include "Character.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "Joystick.h"

USING_NS_CC;

Character::Character() :
	_lifeValue(INITIAL_LIFE_VALUE),
	_experience(0),
	_sorce(0),
	_weaponType(kWeaponArrow),
	_isDie(true)
{
	// �������������ǩ
	setTag(kGlobalCharacter);
}

Character::~Character()
{
}

void Character::addLifeValue(const float &add)
{
	_lifeValue += add;
	_hpSlider->setPercent(_lifeValue);			//����Ѫ����
}

void Character::addExperience(const int &add)
{
	_experience += add;
}

void Character::addSorce(const int &add)
{
	_sorce += add;
}

void Character::attack(const Vec3 &pos)
{
	//CCLOG("Attack success! %f %f %f", pos.x, pos.y, pos.z);
	//CCLOG("start %f %f %f", getPosition3D().x, getPosition3D().y, getPosition3D().z);
	GameScene::getWeaponManager()->createWeapon(kWeaponArrow, this, getPosition3D(), pos);
}

void Character::die()
{
	if (_isDie)return;
	_isDie = true;
	if (getDept() != -1)	// ������������
	{
		GameScene::getCharacterManager()->addCharacterToPool(this);
		//���ò��ɼ�
		setVisible(false);
		// ����ı�����λ�õ� (0,-1,0) ��һ��
		setPosition3D(-Vec3::UNIT_Y * 10);
		// ͬ������������
		syncNodeToPhysics();
	}
	else	//�Լ�����
	{

	}
}

void Character::move(const Vec3 & pos)
{
	/* ��ȡ������� */
	auto s = static_cast<Physics3DRigidBody*>(getPhysicsObj());
	/* �������ٶ�Ϊ�����ƶ��ٶ�*����������Y���򱣳ֺ�ԭ��һ�� */
	s->setLinearVelocity(getAttribute().getMovingSpeed()*pos+Vec3(0,s->getLinearVelocity().y,0));
}

bool Character::init()
{
	/* ������Ѫ���� */
	_hpSlider = Slider::create();
	_hpSlider->loadBarTexture("images/bloodbg.png");
	_hpSlider->loadProgressBarTexture("images/blood.png");
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setScale(.03f);
	_hpSlider->setPercent(_lifeValue);
	_hpSlider->setRotation3D(Vec3(-90,0,0));
	_hpSlider->setPosition3D(getPosition3D()+Vec3::UNIT_Y*2);
	addChild(_hpSlider);

	/* �����ǳ�ʼ������ */
	//initWithFile("Sprite3DTest/box.c3t");
	initWithFile("Sprite3DTest/sphere.c3b");
	setTexture("images/Icon.png");

	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//�ݶ���������������Ϊ50
	//des.shape = Physics3DShape::createBox(Vec3(2.0f, 2.0f, 2.0f));	//�����С
	des.shape = Physics3DShape::createSphere(1.f);

	auto obj = Physics3DRigidBody::create(&des);

	_physicsComponent = Physics3DComponent::create(obj);

	addComponent(_physicsComponent);

	_contentSize = getBoundingBox().size;

	obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// ������ײ��Ļص�����

	obj->setUserData(this);

	setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);	//Ӧ��ͬ��

	setScale(2.f);		//���ô�С
	setVisible(false);	//���ò��ɼ�
	setPosition3D(-Vec3::UNIT_Y*10);	//���ó�ʼ����
	syncNodeToPhysics();
	return true;
}

void Character::initialization()
{
	// ��ʼ��ֵ
	_lifeValue = INITIAL_LIFE_VALUE;
	_experience = 0;
	_sorce = 0;
	_attribute.init();
	_weaponType = kWeaponArrow;
	_isDie = false;
	_hpSlider->setPercent(_lifeValue);			//����Ѫ����

	setVisible(true);							//���ÿɼ�
	// ȡ��֮���������λ�ò�ͬ��
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2, 20, rand() % WORLD_WIDTH - WORLD_WIDTH / 2));

	syncNodeToPhysics();
}

void Character::beAttacked(const Weapons * weapon)
{
	addLifeValue(-weapon->getPower() / 1.0);	//�ܵ������ȵ�Ѫ
	//cout << "life life -------------------------------> " << getLifeValue() << endl;

	// ���Ѫ��С��0��������
	if (getLifeValue() <= 0)
		die();
}

void Character::update(float dt)
{
	if (_dept == -1)
	{
		Vec3 ret = Vec3::ZERO;
		if (GameScene::getJoystick()->getKeyW())
			ret += Vec3(0, 0, -1);
		if (GameScene::getJoystick()->getKeyA())
			ret += Vec3(-1, 0, 0);
		if (GameScene::getJoystick()->getKeyS())
			ret += Vec3(0, 0, 1);
		if (GameScene::getJoystick()->getKeyD())
			ret += Vec3(1, 0, 0);
		if (GameScene::getJoystick()->isFirstView())
		{
			GameScene::getCamera()->setPosition3D(getPosition3D()+Vec3::UNIT_Y*2);
		}
		else
		{
			//GameScene::getCamera()->setPosition3D(getPosition3D()+Vec3(100,50,100));
			//GameScene::getCamera()->lookAt(getPosition3D());
			GameScene::getCamera()->setPosition3D(GameScene::getCamera()->getPosition3D()+ .7*ret.getNormalized());
		}
		move(ret.getNormalized());

		syncNodeToPhysics();
	}
	else if(!_isDie)
	{
		static float attackTime = 0;
		attackTime += dt;
		static Vec3 minn = Vec3::ZERO;
		if (attackTime > 10.f) {
			minn = GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D() - getPosition3D();
			auto other = GameScene::getCharacterManager()->getEnemyCharacter();
			int len = other.size();
			for (std::set<Character*>::iterator i = other.begin(); i != other.end(); i++)
			{
				if (*i != this&&((*i)->getPosition3D() - getPosition3D()).length()<minn.length())
				{
					minn = (*i)->getPosition3D() - getPosition3D();
				}
			}
			attack(minn);
			move(minn.getNormalized());
			attackTime /= 10.f;
		}
	}
}


Character::Attribute::Attribute() :
	_attackDamage(0),
	_attackRange(0),
	_attackSpeed(0),
	_movingSpeed(50.f),
	_empiricalAcquisition(0),
	_defensiveForce(0),
	_restoringAbility(0),
	_temporary(kTemporaryNone),
	_duration(0)
{

}

Character::Attribute::~Attribute()
{

}

void Character::Attribute::addAttackDamage(const float &add)
{
	_attackDamage = max(0.0f, _attackDamage + add);
}

void Character::Attribute::addAttackRange(const float &add)
{
	_attackRange = max(0.0f, _attackRange + add);
}

void Character::Attribute::addAttackSpeed(const float &add)
{
	_attackSpeed = max(0.0f, _attackSpeed + add);
}

void Character::Attribute::addMovingSpeed(const float &add)
{
	_movingSpeed = max(0.0f, _movingSpeed + add);
}

void Character::Attribute::addEmpiricalAcquisition(const float &add)
{
	_empiricalAcquisition = max(0.0f, _empiricalAcquisition + add);
}

void Character::Attribute::addDefensiveForce(const float &add)
{
	_defensiveForce = max(0.0f, _defensiveForce + add);
}

void Character::Attribute::addRestoringAbility(const float &add)
{
	_restoringAbility = max(0.0f, _restoringAbility + add);
}

void Character::Attribute::addView()
{
	_temporary |= kTemporaryView;
}

void Character::Attribute::addSmall()
{
	_temporary |= kTemporarySmall;
}

void Character::Attribute::addMagnet()
{
	_temporary |= kTemporaryMagnet;
}

void Character::Attribute::delView()
{
	_temporary &= ~kTemporaryView;
}

void Character::Attribute::delSmall()
{
	_temporary &= ~kTemporarySmall;
}

void Character::Attribute::delMagnet()
{
	_temporary &= ~kTemporaryMagnet;
}

void Character::Attribute::setDuration(float add)
{
	_duration = max(0.0f, _duration + add);
}

void Character::Attribute::init()
{
	_attackDamage = 0;
	_attackRange = 0;
	_attackSpeed = 0;
	_movingSpeed = 50.f;
	_empiricalAcquisition = 0;
	_defensiveForce = 0;
	_restoringAbility = 0;
}
