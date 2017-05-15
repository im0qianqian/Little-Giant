#include "Weapons.h"

Weapons::Weapons()
{

}

Weapons::~Weapons()
{

}

void *Weapons::getOwner()
{
	return _owner;
}

void Weapons::update(float dt)
{
	
}

bool Weapons::init(void *owner, float power, float speed, float distance, float angle,Vec2 pos)
{
	bool flag = false;
	if (true)
	{
		_owner = owner;
		_power = power;
		_speed = speed;
		_distance = distance;
		_angle = angle;
		_pos = pos;
		flag = true;
	}
	return flag;
}

void Arrow::attack()
{

}

void Bomb::attack()
{

}

void Dart::attack()
{

}