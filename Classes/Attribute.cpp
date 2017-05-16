#include "Attribute.h"
#include "Global.h"

Attribute::Attribute():
	_attackDamage(0),
	_attackRange(0),
	_attackSpeed(0),
	_movingSpeed(0),
	_empiricalAcquisition(0),
	_defensiveForce(0),
	_restoringAbility(0),
	_temporary(kTemporaryNone),
	_duration(0)
{

}

Attribute::~Attribute()
{

}

Attribute* Attribute::create()
{
	Attribute *attribute = new Attribute();
	if (!attribute)
	{
		CCASSERT(attribute, "Attribute not null!");
		delete attribute;
		attribute = NULL;
	}
	return attribute;
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
	_temporary |= kTemporaryView;
}

void Attribute::addSmall()
{
	_temporary |= kTemporarySmall;
}

void Attribute::addMagnet()
{
	_temporary |= kTemporaryMagnet;
}

void Attribute::delView()
{
	_temporary &= ~kTemporaryView;
}

void Attribute::delSmall()
{
	_temporary &= ~kTemporarySmall;
}

void Attribute::delMagnet()
{
	_temporary &= ~kTemporaryMagnet;
}

void Attribute::setDuration(float add)
{
	_duration = max(0.0f, _duration + add);
}
