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

		//draw x
		for (int j = -20; j <= 20; j++)
		{
			_draw->drawLine(Vec3(-100, 0, 5 * j), Vec3(100, 0, 5 * j), Color4F(1, 0, 0, 1));
		}
		//draw z
		for (int j = -20; j <= 20; j++)
		{
			_draw->drawLine(Vec3(5 * j, 0, -100), Vec3(5 * j, 0, 100), Color4F(0, 0, 1, 1));
		}
		//draw y
		_draw->drawLine(Vec3(0, 0, 0), Vec3(0, 250, 0), Color4F(0, 1, 0, 1));
		addChild(_draw);

		auto sprite = Sprite3D::create("orc.c3b");
		sprite->setScale(3.0f);
		sprite->setPosition3D(Vec3(0, 0, 0));
		addChild(sprite);
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