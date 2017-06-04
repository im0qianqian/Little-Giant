#include "StageManager.h"
#include "GameScene.h"

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
		//创建地面
		Physics3DRigidBodyDes rbDes;
		rbDes.mass = 0.0f;
		rbDes.shape = Physics3DShape::createBox(Vec3(WORLD_LENGTH, WORLD_HEIGHT, WORLD_WIDTH));

		_ground = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "Sprite3DTest/plane.png");
		_ground->setScaleX(WORLD_LENGTH);
		_ground->setScaleZ(WORLD_WIDTH);
		_ground->syncNodeToPhysics();
		_ground->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
		addChild(_ground);

		unsigned char* pBuffer = NULL;
		ssize_t bufferSize = 0;
		pBuffer = FileUtils::sharedFileUtils()->getFileData("maps/1.txt", "r", &bufferSize);
		cout << bufferSize << endl;
		cout << pBuffer << endl;
		int x = 0, y = 0, t = 0;
		const auto elementLength = WORLD_LENGTH / MAP_FILE_LENGTH;
		const auto elementWidth = WORLD_WIDTH / MAP_FILE_WIDTH;
		for (int i = 0; i < bufferSize; i++)
		{
			if (pBuffer[i] == '0')
			{
				x += elementLength, t++;
				if (t == MAP_FILE_LENGTH)
				{
					t = 0;
					x = 0;
					y += elementWidth;
				}
			}
			else if (pBuffer[i] == '1')
			{
				rbDes.shape = Physics3DShape::createBox(Vec3(elementLength, ELEMENT_HEIGHT, elementWidth));
				auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
				pd2->setScaleX(elementLength);
				pd2->setScaleY(ELEMENT_HEIGHT);
				pd2->setScaleZ(elementWidth);
				pd2->setOpacity(90);	//透明度
				pd2->setPosition3D(Vec3(x - WORLD_LENGTH / 2, ELEMENT_HEIGHT/2, y - WORLD_WIDTH / 2));
				pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				pd2->syncNodeToPhysics();
				addChild(pd2);
				x += elementLength, t++;
				if (t == MAP_FILE_WIDTH)
				{
					t = 0;
					x = 0;
					y += elementWidth;
				}
			}
		}
		if (pBuffer)
		{
			delete[] pBuffer;
			pBuffer = NULL;
		}
		
		/* */
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

//bool StageManager::init()
//{
//	bool flag = false;
//	do
//	{
//
//
//
//
//
//		flag = true;
//	} while (false);
//	return flag;
//}