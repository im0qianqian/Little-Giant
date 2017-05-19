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
		Physics3DRigidBodyDes rbDes;
		rbDes.mass = 0.0f;
		rbDes.shape = Physics3DShape::createBox(Vec3(60.0f, 1.0f, 60.0f));

		auto floor = PhysicsSprite3D::create("Sprite3DTest/box.c3t", &rbDes);
		floor->setTexture("Sprite3DTest/plane.png");
		floor->setScaleX(60);
		floor->setScaleZ(60);
		addChild(floor);
		//floor->setCameraMask((unsigned int)CameraFlag::USER1);
		floor->syncPhysicsToNode();
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
					sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE);
					//sprite->setCameraMask((unsigned short)CameraFlag::USER1);
					sprite->setScale(0.8f);
					this->addChild(sprite);
				}
			}
		}
		/*
		_camera = Camera::createPerspective(60, (GLfloat)960 / 640, 1, 1000);
		_camera->setCameraFlag(CameraFlag::USER1);
		_camera->setPosition3D(Vec3(0, 100, -100));
		_camera->lookAt(Vec3(0, 0, 0), Vec3::UNIT_Y);
		*/
		/*auto listen = EventListenerTouchAllAtOnce::create();
		
		listen->onTouchesMoved = CC_CALLBACK_2(StageManager::onTouchesMoved, this);
		listen->onTouchesEnded = CC_CALLBACK_2(StageManager::onTouchesEnded,this);
		listen->onTouchesBegan = CC_CALLBACK_2(StageManager::onTouchesBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listen, this);*/

		flag = true;
	} while (false);
	return flag;
}

void StageManager::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	_needShootBox = true;
	event->stopPropagation();
}
void StageManager::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	CCLOG("on Touches ended!");
	if (!_needShootBox) return;
	if (!touches.empty())
	{
		auto location = touches[0]->getLocationInView();

		Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
		nearP = GameScene::getCamera()->unproject(nearP);
		farP = GameScene::getCamera()->unproject(farP);
		Vec3 dir(farP - nearP);
		shootBox(GameScene::getCamera()->getPosition3D() + dir * 10.0f);
		event->stopPropagation();
	}
}

void StageManager::shootBox(const cocos2d::Vec3 &des)
{
	Physics3DRigidBodyDes rbDes;
	Vec3 linearVel = des - GameScene::getCamera()->getPosition3D();
	linearVel.normalize();
	linearVel *= 100.0f;
	rbDes.originalTransform.translate(GameScene::getCamera()->getPosition3D());
	rbDes.mass = 1.f;
	rbDes.shape = Physics3DShape::createBox(Vec3(0.5f, 0.5f, 0.5f));
	auto sprite = PhysicsSprite3D::create("Sprite3DTest/box.c3t", &rbDes);
	sprite->setTexture("images/Icon.png");

	auto rigidBody = static_cast<Physics3DRigidBody*>(sprite->getPhysicsObj());
	rigidBody->setLinearFactor(Vec3::ONE);
	rigidBody->setLinearVelocity(linearVel);
	rigidBody->setAngularVelocity(Vec3::ZERO);
	rigidBody->setCcdMotionThreshold(0.5f);
	rigidBody->setCcdSweptSphereRadius(0.4f);

	this->addChild(sprite);
	sprite->setPosition3D(GameScene::getCamera()->getPosition3D());
	sprite->setScale(0.5f);
	sprite->syncNodeToPhysics();

	//optimize, only sync node to physics
	sprite->setSyncFlag(Physics3DComponent::PhysicsSyncFlag::PHYSICS_TO_NODE); //sync node to physics

	//sprite->setCameraMask((unsigned short)CameraFlag::USER1);
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
		_angley -= CC_DEGREES_TO_RADIANS(delta.y);
		Vec3 c = Vec3(200.0f*sinf(_angle), 200.0f*sinf(_angley), 200.0f*cosf(_angle));
		//Vec3 c = camera->getPosition3D();
		GameScene::getCamera()->setPosition3D(Vec3(200.0f * sinf(_angle), 200.0f * cosf(_angley), 200.0f * (cosf(_angle)+sinf(_angley))));
		//_camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, -100.0f * cosf(_angle)));
		GameScene::getCamera()->lookAt(Vec3(0.0f, 0.0f, 0.0f), Vec3::UNIT_Y);
	}
	event->stopPropagation();
}
