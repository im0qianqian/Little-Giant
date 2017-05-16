#include "Character.h"
#include "Global.h"

Character::Character():
	_lifeValue(INITIAL_LIFE_VALUE),
	_experience(0),
	_sorce(0),
	_weaponType(kWeaponArrow),
	_isDie(false)
{
}

Character::~Character()
{
}

void Character::addLifeValue(float add)
{
	_lifeValue += add;
}

void Character::addExperience(int add)
{
	_experience += add;
}

void Character::addSorce(int add)
{
	_sorce += add;
}

void Character::attack()
{
	switch (_weaponType)
	{
	case kWeaponArrow:
		break;
	case kWeaponBomb:
		break;
	case kWeaponDart:
		break;
	}
}

void Character::die()
{

}
