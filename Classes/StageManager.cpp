#include "StageManager.h"
#include "GameScene.h"
#include "Global.h"

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}
#define START_POS_X -0.5
#define START_POS_Y -2.5
#define START_POS_Z -0.5

#define ARRAY_SIZE_X 4
#define ARRAY_SIZE_Y 3
#define ARRAY_SIZE_Z 4
bool StageManager::init()
{
	bool flag = false;
	do
	{
		Physics3DRigidBodyDes rbDes;
		rbDes.mass = 0.0f;
		rbDes.shape = Physics3DShape::createBox(Vec3(WORLD_LENGTH, WORLD_HEIGHT, WORLD_WIDTH));

		_ground = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "Sprite3DTest/plane.png");
		_ground->setScaleX(WORLD_LENGTH);
		_ground->setScaleZ(WORLD_WIDTH);
		addChild(_ground);
		_ground->setCameraMask((unsigned int)CameraFlag::USER1);
		_ground->syncNodeToPhysics();
		_ground->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
		CCLOG("I am a ground ,my address is & %d", _ground);

		//create several boxes using PhysicsSprite3D
		rbDes.mass = 1.f;
		rbDes.shape = Physics3DShape::createBox(Vec3(0.8f, 0.8f, 0.8f));
		float start_x = START_POS_X - ARRAY_SIZE_X / 2;
		float start_y = START_POS_Y;
		float start_z = START_POS_Z - ARRAY_SIZE_Z / 2;

		for (int k = 0; k < ARRAY_SIZE_Y; k++)
		{
			for (int i = 0; i < ARRAY_SIZE_X; i++)
			{
				for (int j = 0; j < ARRAY_SIZE_Z; j++)
				{
					float x = 1.0*i + start_x;
					float y = 5.0 + 1.0*k + start_y;
					float z = 1.0*j + start_z;

					auto sprite = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
					sprite->setPosition3D(Vec3(x, y, z));
					sprite->syncNodeToPhysics();
					sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
					sprite->setCameraMask((unsigned short)CameraFlag::USER1);
					sprite->setScale(0.8f);
					this->addChild(sprite);
				}
			}
		}
		flag = true;
	} while (false);
	return flag;
}