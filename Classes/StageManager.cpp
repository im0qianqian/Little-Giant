#include "StageManager.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include <fstream>
#include <thread>

StageManager::StageManager() :
	_ground(nullptr),
	_sun(nullptr),
	_characterLight(nullptr)
{
	memset(_map, 0, sizeof(_map));
	memset(_cMap, 0, sizeof(_cMap));
	cout << "StageManager 构造" << endl;
}

StageManager::~StageManager()
{
	cout << "StageManager 析构" << endl;
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
		if (GameScene::getGameMode() == kGameModeNight)	// 如果当前游戏属于黑夜模式
		{
			/* 创建灯光 */
			createLight();
			/* 启动定时器更新 */
			scheduleUpdate();
		}
		/* 每两秒更新一次所有人的位置 */
		schedule(schedule_selector(StageManager::updateMap), 2.f);
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
		angle -= 0.005f;
	}), nullptr)));

	addChild(_characterLight);
	addChild(_sun);
}

void StageManager::createObstacles()
{
	string pBuffer = FileUtils::getInstance()->getStringFromFile("maps/" + to_string(rand()%3) + ".txt");
	cout << pBuffer << endl;
	cout << pBuffer.length() << endl;

	const int elementLength = WORLD_LENGTH / MAPS_FILE_LENGTH;
	const int elementWidth = WORLD_WIDTH / MAPS_FILE_WIDTH;
	for (int i = 0; i < MAPS_FILE_WIDTH; i++)
	{
		for (int j = 0; j < MAPS_FILE_LENGTH; j++)
		{
			_map[i][j] = pBuffer[i*(MAPS_FILE_WIDTH + 2) + j] - '0';
		}
	}
	int count, m, n;
	m = elementLength, n = 2;
	for (int i = 0; i < MAPS_FILE_WIDTH; i++)
	{
		for (int j = 0; j < MAPS_FILE_LENGTH; j++)
		{
			count = 0;
			while (_map[i][j] == 1&&j<MAPS_FILE_LENGTH)
			{
				count++;
				j++;
			}
			if (count > 1)
			{
				Physics3DRigidBodyDes rbDes;
				rbDes.shape = Physics3DShape::createBox(Vec3(m*count*1.f, ELEMENT_HEIGHT*1.f, n*1.f));
				auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
				pd2->setScaleX(m*count*1.f);
				pd2->setScaleY(ELEMENT_HEIGHT*1.f);
				pd2->setScaleZ(n*1.f);
				pd2->setPosition3D(Vec3((j)*elementLength - (count + 1)*elementLength / 2 - WORLD_LENGTH / 2*1.f, ELEMENT_HEIGHT / 2*1.f, i*elementWidth - WORLD_WIDTH / 2*1.f));
				addChild(pd2);
				pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				pd2->syncNodeToPhysics();

			}
		}
	}
	m = 2, n = elementLength;
	for (int i = 0; i < MAPS_FILE_LENGTH; i++)
	{
		for (int j = 0; j < MAPS_FILE_WIDTH; j++)
		{
			count = 0;
			while (_map[j][i] == 1 && j<MAPS_FILE_WIDTH)
			{
				count++;
				j++;
			}
			if (count > 1)
			{
				
				Physics3DRigidBodyDes rbDes;
				rbDes.shape = Physics3DShape::createBox(Vec3(m*1.f, ELEMENT_HEIGHT*1.f, n*count*1.f));
				auto pd2 = Stage::create(&rbDes, "Sprite3DTest/box.c3t", "images/CyanSquare.png");
				pd2->setScaleX(m*1.f);
				pd2->setScaleY(ELEMENT_HEIGHT*1.f);
				pd2->setScaleZ(n*count*1.f);
				pd2->setPosition3D(Vec3(i*elementWidth - WORLD_LENGTH / 2*1.f, ELEMENT_HEIGHT / 2*1.f, j*elementLength - (count + 1)*elementLength / 2 - WORLD_WIDTH / 2*1.f));
				addChild(pd2);
				pd2->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);
				pd2->syncNodeToPhysics();
			}
		}
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

void StageManager::getCMap(int map[MAPS_FILE_WIDTH][MAPS_FILE_LENGTH])
{
	memcpy(map, _cMap, sizeof(_cMap));
}

void StageManager::updateMap(float dt)
{
	//thread([this]()
	{
		auto multVec = [&](const Vec3 &pos)
		{
			return Vec2(int((pos.z + WORLD_WIDTH / 2)*MAPS_FILE_WIDTH / WORLD_WIDTH)*1.f, int((pos.x + WORLD_LENGTH / 2)*MAPS_FILE_LENGTH / WORLD_LENGTH)*1.f);
		};
		memset(_cMap, 0, sizeof(_cMap));
		auto award = GameScene::getAwardManager()->getAllAward();
		for (auto i : award)
		{
			auto pos = multVec(i->getPosition3D());
			if (pos.x < 0 || pos.x >= MAPS_FILE_WIDTH || pos.y < 0 || pos.y >= MAPS_FILE_LENGTH)continue;
			_cMap[int(pos.x)][int(pos.y)] = kGlobalAward;
		}
		/* 敌人部分 */
		auto enemy = GameScene::getCharacterManager()->getEnemyCharacter();
		for (auto i : enemy)
		{
			auto pos = multVec(i->getPosition3D());
			if (pos.x < 0 || pos.x >= MAPS_FILE_WIDTH || pos.y < 0 || pos.y >= MAPS_FILE_LENGTH)continue;
			_cMap[int(pos.x)][int(pos.y)] = kGlobalCharacter;
		}
		/* 玩家部分 */
		auto my = multVec(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D());
		_cMap[int(my.x)][int(my.y)] = kGlobalCharacter;
	}//).detach();
	
}

void StageManager::update(float dt)
{
	if (GameScene::getCharacterManager()->getPlayerCharacter() != nullptr)
	{
		// 人物灯光一直跟随主角
		getCharacterLight()->setPosition3D(GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D());
	}
}
