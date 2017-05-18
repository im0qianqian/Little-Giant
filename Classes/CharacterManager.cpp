#include "CharacterManager.h"

CharacterManager::CharacterManager()
{
}

CharacterManager::~CharacterManager()
{
}

bool CharacterManager::init()
{
	createCharacter(kCharacterPlayer);
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
	/* ����һ������ */
	Physics3DRigidBodyDes des;
	des.mass = 50.f;			//�ݶ���������������Ϊ50
	des.shape = Physics3DShape::createBox(Vec3(0.5f, 1.0f, 0.5f));	//��������ΪBox
	auto character = Character::create("Sprite3DTest/box.c3t", &des);
	character->setTexture("images/Icon.png");						//���ò���
	character->setPosition3D(Vec3(0,10,0));
	character->setScale(2.0f);
	character->syncNodeToPhysics();
	addChild(character);

	return static_cast<Character*> (character);
}
