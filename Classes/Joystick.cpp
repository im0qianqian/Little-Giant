#include "Joystick.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"

Joystick::Joystick() :
	_keyW(false),
	_keyA(false),
	_keyS(false),
	_keyD(false),
	_listenerKeyboard(nullptr),
	_listenerTouch(nullptr),
	_isFirstView(false)
{
}

Joystick::~Joystick()
{
}

bool Joystick::init()
{
	keyboardListen();
	touchListen();
	return true;
}

void Joystick::setKeyState(const EventKeyboard::KeyCode &keyCode, const bool &state)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		_keyW = state;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		_keyA = state;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		_keyS = state;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		_keyD = state;
		break;
	default:
		break;
	}
}


void Joystick::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	event->stopPropagation();
}

void Joystick::onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	CCLOG("on Touches ended!!!");
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocationInView();
		Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
		nearP = GameScene::getCamera()->unproject(nearP);
		farP = GameScene::getCamera()->unproject(farP);
		Vec3 dir(farP - nearP);
		float dist = 0.0f;
		float ndd = Vec3::dot(Vec3(0, 1, 0), dir);
		float ndo = Vec3::dot(Vec3(0, 1, 0), nearP);
		dist = (0 - ndo) / ndd;
		Vec3 p = nearP + dist *  dir;
		//CCLOG("%f %f %f", getPlayerCharacter()->getPosition3D().x, getPlayerCharacter()->getPosition3D().y, getPlayerCharacter()->getPosition3D().z);
		CCLOG("manag %f %f %f", p.x, p.y, p.z);
		GameScene::getCharacterManager()->getPlayerCharacter()->attack(p);
		event->stopPropagation();
	}
}

void Joystick::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event)
{
	if (!touches.empty())
	{
		auto touch = touches[0];
		auto delta = touch->getDelta();
		if (!_isFirstView)
		{
			static float _angle = 0.f;
			//static float _angley = 0.f;
			_angle -= CC_DEGREES_TO_RADIANS(delta.x);
			//_angley -= CC_DEGREES_TO_RADIANS(delta.y);
			Vec3 cam = GameScene::getCharacterManager()->getPlayerCharacter()->getPosition3D();
			//CCLOG("cam  --> %f %f %f", cam.x, cam.y, cam.z);
			//Vec3 c = Vec3(200.0f*sinf(_angle)+ cam.x, 200.0f*sinf(_angley) + cam.y, 200.0f*cosf(_angle) + cam.z);
			Vec3 c = Vec3(100.0f * sinf(_angle) + cam.x, 50.0f + cam.y, -100.0f * cosf(_angle) + cam.z);
			//Vec3 c = camera->getPosition3D();
			//GameScene::getCamera()->setPosition3D(c);
			//_camera->setPosition3D(Vec3(100.0f * sinf(_angle), 50.0f, -100.0f * cosf(_angle)));
			//GameScene::getCamera()->lookAt(cam);
		}
		else
		{
			// 第一人称视角
			Vec3 rot = GameScene::getCamera()->getRotation3D();
			rot.y += delta.x;
			GameScene::getCamera()->setRotation3D(rot);
			GameScene::getCharacterManager()->getPlayerCharacter()->setRotation3D(rot);
		}
		
	}
	event->stopPropagation();
}



std::function<void(const Physics3DCollisionInfo&ci)> Joystick::onPhysics3DCollision()
{
	return [&](const Physics3DCollisionInfo&ci)
	{
		if (!ci.collisionPointList.empty()) {
			/* 获取两个碰撞对象 */
			auto *objA = static_cast<Node*>(ci.objA->getUserData());
			auto *objB = static_cast<Node*>(ci.objB->getUserData());
			//CCASSERT(objA, "OBJ A NULL");
			//CCASSERT(objB, "OBJ B NULL");
			if (objA != NULL && objB != NULL)
			{
				bool flag = true;	// 是否输出碰撞 Tag 调试使用

				//判断位置合法，暂用(场外位置不考虑碰撞)
				if (ci.collisionPointList[0].worldPositionOnB.y < 0)return;

				if (gObjectEqual(objA->Node::getTag(), objB->Node::getTag(), kGlobalWeapon, kGlobalStage))		//武器与障碍物碰撞
				{
					// 创建光效
					createParticle(ci.collisionPointList[0].worldPositionOnB);

					CCLOG("---------------- weapon stage --------------------");
					// 如果 A 是障碍物的话交换，最终结果： A 武器、B 障碍物
					if (objA->Node::getTag() == kGlobalStage)
						swap(objA, objB);
					Weapons *weapon = dynamic_cast<Weapons*>(objA);
					weapon->destroy();
				}
				else if (gObjectEqual(objA->Node::getTag(), objB->Node::getTag(), kGlobalWeapon, kGlobalCharacter))	//武器与人物碰撞
				{
					// 创建光效
					createParticle(ci.collisionPointList[0].worldPositionOnB);

					CCLOG("---------------- weapon character --------------------");
					// 如果 A 是武器的话交换，最终结果： A 人物、B 武器
					if (objA->Node::getTag() == kGlobalWeapon)
						swap(objA, objB);
					Weapons *weapon = dynamic_cast<Weapons*>(objB);
					Character *character = dynamic_cast<Character*>(objA);
					// 人物受到攻击
					character->beAttacked(weapon);
					// 删除武器对象
					weapon->destroy();
				}
				else if (gObjectEqual(objA->Node::getTag(), objB->Node::getTag(), kGlobalWeapon, kGlobalWeapon))	//武器与武器碰撞
				{
					// 创建光效
					createParticle(ci.collisionPointList[0].worldPositionOnB);

					CCLOG("---------------- weapon weapon --------------------");
					Weapons *weapon1 = dynamic_cast<Weapons*>(objA);
					Weapons *weapon2 = dynamic_cast<Weapons*>(objB);
					// 删除武器对象
					weapon1->destroy();
					weapon2->destroy();
				}
				else if (gObjectEqual(objA->Node::getTag(), objB->Node::getTag(), kGlobalAward, kGlobalCharacter))
				{
					CCLOG("---------------- Award character --------------------");
					// 如果 A 是武器的话交换，最终结果： A 人物、B 奖励
					if (objA->Node::getTag() == kGlobalAward)
						swap(objA, objB);
					Award * award = dynamic_cast<Award*>(objB);
					award->destroy();
				}
				else
				{
					flag = false;
				}
				if (flag)	// 仅用调试 输出标签
				{
					CCLOG("tag aa : %d", objA->Node::getTag());
					CCLOG("tag bb : %d", objB->Node::getTag());
				}
			}
		}
	};
}

void Joystick::createParticle(const Vec3 &pos)
{
	/* 武器碰撞粒子特效 */
	auto ps = PUParticleSystem3D::create("C:/Cocos/Cocos2d-x/cocos2d-x-3.10/tests/cpp-tests/Resources/Particle3D/scripts/mp_hit_04.pu");
	ps->setPosition3D(pos);
	ps->setScale(0.05f);
	ps->startParticleSystem();
	ps->setCameraMask((unsigned int)CameraFlag::USER1);
	GameScene::getWeaponManager()->addChild(ps);
	ps->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]() {
		ps->removeFromParent();
	}), nullptr));
}

void Joystick::keyboardListen()
{
	/* 创建键盘监听器 */
	_listenerKeyboard = EventListenerKeyboard::create();
	/* 键盘被按下 */
	_listenerKeyboard->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		setKeyState(keyCode, true);
		/* 方便调试 设置 Debug 模式*/
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			if (SceneManager::getScene()->getPhysics3DWorld()->isDebugDrawEnabled())
				SceneManager::getScene()->getPhysics3DWorld()->setDebugDrawEnable(false);
			else SceneManager::getScene()->getPhysics3DWorld()->setDebugDrawEnable(true);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_Q)	//视角变换
		{
			_isFirstView = !_isFirstView;
			if (_isFirstView)
			{
				/* 第一人称视角时相机要保持水平方向 */
				Vec3 pos = GameScene::getCamera()->getRotation3D();
				pos.x = pos.z = 0;
				GameScene::getCamera()->setRotation3D(pos);
			}
		}
		/* ----------------------- */
		log("Keyboard %d Pressed~", keyCode);
	};
	/* 键盘弹起 */
	_listenerKeyboard->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event *event)
	{
		CCLOG("Keyboard %d Released~", keyCode);
		setKeyState(keyCode, false);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerKeyboard, this);
}

void Joystick::touchListen()
{
	_listenerTouch = EventListenerTouchAllAtOnce::create();
	_listenerTouch->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
	_listenerTouch->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
	_listenerTouch->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerTouch, this);
}

