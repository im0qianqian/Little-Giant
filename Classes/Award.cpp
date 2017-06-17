#include "Award.h"
#include "GameScene.h"
#include "Joystick.h"
#include "Global.h"

Award::Award() :
	_isDeleted(true),
	_awardType(AwardType::kAwardEXP)
{
	// 武器标签
	setTag(kGlobalAward);
}

Award::~Award()
{
}

bool Award::init()
{
	bool flag = false;
	do
	{
		if (initWithFile("images/3.c3b"))								//设置形状
		{
			Physics3DRigidBodyDes rbDes;										//定义一个三维空间刚体
			rbDes.mass = 0.f;													//设置刚体质量
			rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));	//刚体大小
			auto obj = Physics3DRigidBody::create(&rbDes);						//创建刚体对象

			_physicsComponent = Physics3DComponent::create(obj);				//利用该刚体对象创建组件

			addComponent(_physicsComponent);

			_contentSize = getBoundingBox().size;

			obj->setCollisionCallback(GameScene::getJoystick()->onPhysics3DCollision());	// 设置碰撞后的回调函数

			obj->setUserData(this);

			setScale(.007f);										//大小缩放到0.007倍
			setRotation3D(Vec3(90, 0, 0));							//旋转

			setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);	//应用同步
			flag = true;
		}
	} while (false);
	return flag;
}

void Award::initialization()
{
	_isDeleted = false;

	// 取出之后随机设置位置并同步
	setPosition3D(Vec3(rand() % WORLD_LENGTH - WORLD_LENGTH / 2, 0, rand() % WORLD_WIDTH - WORLD_WIDTH / 2) + 2 * Vec3::UNIT_Y);
	randomType();

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

void Award::collisionWithCharacter(Character * const & character)
{
	// 如果奖励已经给了别人就不能再给了，如果对方死亡的话也不能被得到
	if (isDeleted() || character->isDie())return;
	// 将奖励给人物
	applyToCharacter(character);
	// 自身销毁
	destroy();
}

void Award::applyToCharacter(Character * const & character)
{
	switch (_awardType)
	{
	case kAwardHP:
		character->addLifeValue(10.f);
		break;
	case kAwardEXP:
		character->addExperience(3.f);
		break;
	case kAwardSorce:
		character->addSorce(3.f);
		break;
	default:
		break;
	}
}

void Award::randomType()
{
	/* 随机确定奖励类型 */
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
