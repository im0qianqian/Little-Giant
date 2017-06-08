#include "StageManager.h"
#include "GameScene.h"
#include "Global.h"

StageManager::StageManager() :
	_ground(nullptr),
	_sun(nullptr),
	_characterLight(nullptr),
	_isTurnOnLight(true)
{
}

StageManager::~StageManager()
{
}

bool StageManager::init()
{
	bool flag = false;
	do
	{
		/* 创建地面 */
		createGround();
		/* 创建障碍物 */
		createObstacles();
		if (_isTurnOnLight)		//如果打开了光照系统
		{
			/* 创建灯光 */
			createLight();
			/* 启动定时器更新 */
			scheduleUpdate();
		}
		flag = true;
	} while (false);
	return flag;
}

void StageManager::createLight()
{
	// 人物小灯
	_characterLight = PointLight::create(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D(), Color3B::WHITE, 50.f);
	// 设置灯光亮度
	_characterLight->setIntensity(.5f);

	// 太阳围绕旋转的半径
	float radius = 1000.f;
	_sun = DirectionLight::create(Vec3::ZERO, Color3B::WHITE);
	_sun->runAction(RepeatForever::create(Sequence::create(CallFuncN::create([radius](Node *node) {
		static float angle = 0.0;
		node->setPosition3D(Vec3(radius * cos(angle), radius * sin(angle), 0.0f));
		dynamic_cast<DirectionLight*>(node)->setDirection(Vec3::ZERO - node->getPosition3D());
		angle -= 0.001f;
	}), nullptr)));

	addChild(_characterLight);
	addChild(_sun);
}

void StageManager::createObstacles()
{
	unsigned char* pBuffer = NULL;
	Physics3DRigidBodyDes rbDes;
	ssize_t bufferSize = 0;
	char arr[MAPS_FILE_WIDTH + 2][MAPS_FILE_LENGTH + 2];
	pBuffer = FileUtils::sharedFileUtils()->getFileData("maps/1.txt", "r", &bufferSize);
	CCLOG("%ld", bufferSize);
	CCLOG("%s", pBuffer);
	int p = 0, q = 0;
	bool f;
	const int elementLength = WORLD_LENGTH / MAPS_FILE_LENGTH;
	const int elementWidth = WORLD_WIDTH / MAPS_FILE_WIDTH;
	for (int i = 0; i < bufferSize; i++)
	{
		if (pBuffer[i] == '1' || pBuffer[i] == '0')
		{
			arr[p][q] = pBuffer[i];
			q++;
			f = true;
		}
		else if (q >= MAPS_FILE_LENGTH && f == true)
		{
			f = false;
			p++;
			q = 0;
		}
	}
	int count, m, n;
	m = elementLength, n = 2;
	for (int i = 0; i < MAPS_FILE_WIDTH; i++)
	{
		for (int j = 0; j < MAPS_FILE_LENGTH; j++)
		{
			count = 0;
			while (arr[i][j] == '1')
			{
				count++;
				j++;
			}
			if (count > 1)
			{
				rbDes.shape = Physics3DShape::createBox(Vec3(m*count, ELEMENT_HEIGHT, n));
				auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
				pd2->setScaleX(m*count);
				pd2->setScaleY(ELEMENT_HEIGHT);
				pd2->setScaleZ(n);
				pd2->setPosition3D(Vec3((j)*elementLength - (count + 1)*elementLength / 2 - WORLD_LENGTH / 2, ELEMENT_HEIGHT / 2, i*elementWidth - WORLD_WIDTH / 2));
				addChild(pd2);
				pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				pd2->syncNodeToPhysics();

			}
		}
	}
	m = 2, n = elementLength;
	for (int i = 0; i < MAPS_FILE_WIDTH; i++)
	{
		for (int j = 0; j < MAPS_FILE_LENGTH; j++)
		{
			count = 0;
			while (arr[j][i] == '1')
			{
				count++;
				j++;
			}
			if (count > 1)
			{
				rbDes.shape = Physics3DShape::createBox(Vec3(m, ELEMENT_HEIGHT, n*count));
				auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
				pd2->setScaleX(m);
				pd2->setScaleY(ELEMENT_HEIGHT);
				pd2->setScaleZ(n*count);
				pd2->setPosition3D(Vec3(i*elementWidth - WORLD_LENGTH / 2, ELEMENT_HEIGHT / 2, j*elementLength - (count + 1)*elementLength / 2 - WORLD_WIDTH / 2));
				addChild(pd2);
				pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				pd2->syncNodeToPhysics();
			}
		}
	}
	if (pBuffer)
	{
		delete[] pBuffer;
		pBuffer = NULL;
	}
}

void StageManager::createGround()
{
	//创建地面
	Physics3DRigidBodyDes rbDes;
	rbDes.mass = 0.0f;
	rbDes.shape = Physics3DShape::createBox(Vec3(WORLD_LENGTH, WORLD_HEIGHT, WORLD_WIDTH));

	_ground = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/sss.jpg");
	_ground->setScaleX(WORLD_LENGTH);
	_ground->setScaleZ(WORLD_WIDTH);
	_ground->syncNodeToPhysics();
	_ground->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
	addChild(_ground);
}

void StageManager::update(float dt)
{
	// 人物灯光一直跟随主角
	getCharacterLight()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D());
}
