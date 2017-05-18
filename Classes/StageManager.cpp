#include "StageManager.h"
#include "DrawNode3D.h"

StageManager::StageManager()
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
		DrawNode3D* _draw = DrawNode3D::create();

<<<<<<< HEAD
		auto floor = PhysicsSprite3D::create("Sprite3DTest/box.c3t", &rbDes);
		floor->setTexture("Sprite3DTest/plane.png");
		floor->setScaleX(60);
		floor->setScaleZ(60);
		this->addChild(floor);
		floor->setCameraMask((unsigned short)CameraFlag::USER1);
		floor->syncNodeToPhysics();
		//static object sync is not needed
		floor->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NONE);

		//create several boxes using PhysicsSprite3D
		rbDes.mass = 1.f;
		rbDes.shape = Physics3DShape::createBox(Vec3(0.8f, 0.8f, 0.8f));
		float start_x = START_POS_X - ARRAY_SIZE_X / 2;
		float start_y = START_POS_Y;
		float start_z = START_POS_Z - ARRAY_SIZE_Z / 2;
		
		for (int k = 0; k<ARRAY_SIZE_Y; k++)
		{
			for (int i = 0; i<ARRAY_SIZE_X; i++)
			{
				for (int j = 0; j<ARRAY_SIZE_Z; j++)
				{
					float x = 1.0*i + start_x;
					float y = 5.0 + 1.0*k + start_y;
					float z = 1.0*j + start_z;

					auto sprite = PhysicsSprite3D::create("Sprite3DTest/box.c3t", &rbDes);
					sprite->setTexture("images/CyanSquare.png");
					sprite->setPosition3D(Vec3(x, y, z));
					sprite->syncNodeToPhysics();
					sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::NODE_AND_NODE);
					//sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
					sprite->setCameraMask((unsigned short)CameraFlag::USER1);
					sprite->setScale(0.8f);
					this->addChild(sprite);
				}
			}
=======
		//draw x
		for (int j = -20; j <= 20; j++)
		{
			_draw->drawLine(Vec3(-100, 0, 5 * j), Vec3(100, 0, 5 * j), Color4F(1, 0, 0, 1));
>>>>>>> parent of e11770a... init
		}
		//draw z
		for (int j = -20; j <= 20; j++)
		{
			_draw->drawLine(Vec3(5 * j, 0, -100), Vec3(5 * j, 0, 100), Color4F(0, 0, 1, 1));
		}
<<<<<<< HEAD
<<<<<<< HEAD
		//draw y
		_draw->drawLine(Vec3(0, 0, 0), Vec3(0, 250, 0), Color4F(0, 1, 0, 1));
		addChild(_draw);

		auto sprite = Sprite3D::create("orc.c3b");
		sprite->setScale(3.0f);
		sprite->setPosition3D(Vec3(0, 0, 0));
		addChild(sprite);
=======

>>>>>>> parent of 4ebe0ea... init
=======

>>>>>>> parent of 4ebe0ea... init
		_camera = Camera::createPerspective(60, (GLfloat)960 / 640, 1, 1000);
		_camera->setCameraFlag(CameraFlag::USER1);
		_camera->setPosition3D(Vec3(0, 100, -100));
		_camera->lookAt(Vec3(0, 0, 0), Vec3::UNIT_Y);

		auto listen = EventListenerTouchAllAtOnce::create();
		listen->onTouchesMoved = CC_CALLBACK_2(StageManager::onTouchesMoved, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);
		addChild(_camera);
		setCameraMask(2);
		flag = true;
	} while (false);
	return flag;
}

void StageManager::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	if (!touches.empty())
	{
		auto touch = touches[0];
		auto delta = touch->getDelta();
		static float _angle = 0.f;
		static float _angley = 0.f;
		_angle -= CC_DEGREES_TO_RADIANS(delta.x);
		//_angley -= CC_DEGREES_TO_RADIANS(delta.y);
		//Vec3 c = camera->getPosition3D();
		//camera->setPosition3D(Vec3(200.0f * sinf(_angle), 200.0f * cosf(_angley), 200.0f * (cosf(_angle)+sinf(_angley))));
		_camera->setPosition3D(Vec3(100.0f * sinf(_angle), 100.0f, -100.0f * cosf(_angle)));
		_camera->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3::UNIT_Y);
	}
}