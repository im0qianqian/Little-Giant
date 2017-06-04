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
#define MAXN 5000
char array[MAXN][MAXN];
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
		addChild(_ground);
		_ground->setCameraMask((unsigned int)CameraFlag::USER1);
		_ground->syncNodeToPhysics();
		_ground->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);

		std::string fullPath = FileUtils::sharedFileUtils()->fullPathForFilename("b.txt");
		unsigned char* pBuffer = NULL;
		ssize_t bufferSize = 0;
		pBuffer = FileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);
		CCLOG("%ld", bufferSize);
		CCLOG("%s", pBuffer);
		int p = 0, q = 0;
		bool f;
		for (int i = 0; i < bufferSize; i++)
		{
			if (pBuffer[i] == '1' || pBuffer[i] == '0')
			{
				array[p][q] = pBuffer[i];
				q++;
				f = true;
			}
			else if (q>=50 && f == true)
			{
				f = false;
				p++;
				q = 0;
			}
		}
		int count,m,n;
		m = ELEMENT_LENGTH, n = 2;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				count = 0;
				while (array[i][j] == '1')
				{
					count++;
					j++;
				}
				if (count>1)
				{
					rbDes.shape = Physics3DShape::createBox(Vec3(m*count, 20, n));
					auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
					pd2->setScaleX(m*count);
					pd2->setScaleY(20);
					pd2->setScaleZ(n);
					pd2->setPosition3D(Vec3((j)*ELEMENT_LENGTH - (count+1)*ELEMENT_LENGTH / 2 - WORLD_LENGTH / 2, 0, i*ELEMENT_WIDTH - WORLD_WIDTH / 2));
					addChild(pd2);
					pd2->setCameraMask((unsigned int)CameraFlag::USER1);
					pd2->syncNodeToPhysics();
					pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				}
			}
		}
		m = 2, n = ELEMENT_LENGTH;
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				count = 0;
				while (array[j][i] == '1')
				{
					count++;
					j++;
				}
				if (count>1)
				{
					rbDes.shape = Physics3DShape::createBox(Vec3(m, 20, n*count));
					auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
					pd2->setScaleX(m);
					pd2->setScaleY(20);
					pd2->setScaleZ(n*count);
					pd2->setPosition3D(Vec3(i*ELEMENT_WIDTH - WORLD_LENGTH / 2, 0, j*ELEMENT_LENGTH - (count+1)*ELEMENT_LENGTH / 2 - WORLD_WIDTH / 2));
					addChild(pd2);
					pd2->setCameraMask((unsigned int)CameraFlag::USER1);
					pd2->syncNodeToPhysics();
					pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				}
			}
		}
		/*int x = 0, y = 0, t = 0;
		for (int i = 0; i < bufferSize; i++)
		{
			Physics3DRigidBodyDes rbDes;
			if (pBuffer[i] == '0')
			{
				x += ELEMENT_LENGTH, t++;
				if (t == 50)
				{
					t = 0;
					x = 0;
					y += ELEMENT_WIDTH;
				}
			}
			else if (pBuffer[i] == '1')
			{
				int m, n;
				if (pBuffer[i - 1] == '1' || pBuffer[i + 1] == '1')
					m = ELEMENT_LENGTH, n = 2;
				else if (pBuffer[i - 1] == '0'&&pBuffer[i + 1] == '0')
					m = 2, n = ELEMENT_LENGTH;
				rbDes.shape = Physics3DShape::createBox(Vec3(m,  20, n));
				auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
				pd2->setScaleX(m);
				pd2->setScaleY(20);
				pd2->setScaleZ(n);
				pd2->setPosition3D(Vec3(x - WORLD_LENGTH / 2, 0, y - WORLD_WIDTH / 2));
				addChild(pd2);
				pd2->setCameraMask((unsigned int)CameraFlag::USER1);
				pd2->syncNodeToPhysics();
				pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				x += ELEMENT_LENGTH, t++;
				if (t == 50)
				{
					t = 0;
					x = 0;
					y += ELEMENT_WIDTH;
				}
			}
		}*/
		if (pBuffer)
		{
			delete[] pBuffer;
			pBuffer = NULL;
		}
		/* */
		//create several boxes using PhysicsSprite3D
		/*rbDes.mass = 1.f;
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
		}*/
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