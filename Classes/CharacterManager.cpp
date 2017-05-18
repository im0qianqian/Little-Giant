#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
}

CharacterManager::~CharacterManager()
{
}

bool CharacterManager::init()
{
	createCharacter(kCharacterEnemy);
	return true;
}

void CharacterManager::pauseGame()
{
}

void CharacterManager::resumeGame()
{
}

Character* CharacterManager::createCharacter(CharacterType characterType)
{
	CCLOG("Character manager");
	/* 创建一个刚体 */
	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//暂定，人物质量设置为50
	des.shape = Physics3DShape::createBox(Vec3(0.5f, 1.0f, 0.5f));	//刚体类型为Box
	auto character = Character::create("Sprite3DTest/box.c3t", &des);
	character->setTexture("images/Icon.png");						//设置材质
	character->setPosition3D(Vec3(0,10,0));
	character->setScale(1.0f);
	character->syncNodeToPhysics();
	character->setCameraMask((unsigned int)CameraFlag::USER2);
	addChild(character);

	_camera = Camera::createPerspective(60, (GLfloat)960 / 640, 1, 1000);
	_camera->setCameraFlag(CameraFlag::USER2);
	_camera->setPosition3D(Vec3(0, 100, -100));
	_camera->lookAt(Vec3(0, 0, 0), Vec3::UNIT_Y);
	setCameraMask((unsigned int)CameraFlag::USER2);
	addChild(_camera);
	return static_cast<Character*> (character);
}
