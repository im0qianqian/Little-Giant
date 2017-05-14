#include "Attribute.h"
#include "Global.h"

Attribute::Attribute()
{

}

Attribute::~Attribute()
{

}

void Attribute::update(float dt)
{

}

Attribute* Attribute::create(float attackDamage, float attackRange, float attackSpeed, float movingSpeed, float empiricalAcquisition, float defensiveForce, float restoringAbility, short int temporary, float duration)
{
	Attribute *attribute = new Attribute();
	if (attribute&&attribute->init(attackDamage, attackRange, attackSpeed, movingSpeed, empiricalAcquisition, defensiveForce, restoringAbility, temporary, duration))
	{
		attribute->autorelease();
	}
	else
	{
		delete attribute;
		attribute = NULL;
	}
	return attribute;
}

bool Attribute::init(float attackDamage, float attackRange, float attackSpeed, float movingSpeed, float empiricalAcquisition, float defensiveForce, float restoringAbility, short int temporary, float duration)
{
	bool flag = true;
	if (true)
	{
		_attackDamage = attackDamage;
		_attackRange = attackRange;
		_attackSpeed = attackSpeed;
		_movingSpeed = movingSpeed;
		_empiricalAcquisition = empiricalAcquisition;
		_defensiveForce = defensiveForce;
		_restoringAbility = restoringAbility;
		_temporary = temporary;
		_duration = duration;
		flag = true;
	}
	return flag;
}

void Attribute::addAttackDamage(float add)
{
	_attackDamage = max(0.0f, _attackDamage + add);
}

void Attribute::addAttackRange(float add)
{
	_attackRange = max(0.0f, _attackRange + add);
}

void Attribute::addAttackSpeed(float add)
{
	_attackSpeed = max(0.0f, _attackSpeed + add);
}

void Attribute::addMovingSpeed(float add)
{
	_movingSpeed = max(0.0f, _movingSpeed + add);
}

void Attribute::addEmpiricalAcquisition(float add)
{
	_empiricalAcquisition = max(0.0f, _empiricalAcquisition + add);
}

void Attribute::addDefensiveForce(float add)
{
	_defensiveForce = max(0.0f, _defensiveForce + add);
}

void Attribute::addRestoringAbility(float add)
{
	_restoringAbility = max(0.0f, _restoringAbility + add);
}

void Attribute::addView()
{
	_temporary |= Temporary_View;
}

void Attribute::addSmall()
{
	_temporary |= Temporary_Small;
}

void Attribute::addMagnet()
{
	_temporary |= Temporary_Magnet;
}

void Attribute::delView()
{
	_temporary &= ~Temporary_View;
}

void Attribute::delSmall()
{
	_temporary &= ~Temporary_Small;
}

void Attribute::delMagnet()
{
	_temporary &= ~Temporary_Magnet;
}

void Attribute::setDuration(float add)
{
	_duration = max(0.0f, _duration + add);
}
