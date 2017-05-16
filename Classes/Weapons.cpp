#include "Weapons.h"

Weapons::Weapons()
{

}

Weapons::~Weapons()
{

}

void Weapons::update(float dt)
{
	
}

bool Weapons::init(void *owner, float power, float speed, float distance, float angle,Vec3 pos)
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
	CCLOG("Arrow attck: %g %g",_position.x, _position.y);
}

void Bomb::attack()
{
	CCLOG("Bomb attck: %g %g", _position.x, _position.y);
}

void Dart::attack()
{
	CCLOG("Dart attck: %g %g", _position.x, _position.y);
}