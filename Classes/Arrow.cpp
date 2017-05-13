#include "Arrow.h"

Arrow::Arrow()
{

}
Arrow::~Arrow()
{

}

Arrow* Arrow::create(void *owner, float power, float speed, float distance, Vec2 pos, AttackType attackType, float direction)
{
	Arrow *arrow = new Arrow();
	if (arrow&&arrow->init(owner, power, speed, distance, pos, attackType, direction))
	{
		arrow->autorelease();
	}
	else
	{
		delete arrow;
		arrow = NULL;
	}
	return arrow;
}

bool Arrow::init(void *owner, float power, float speed, float distance, Vec2 pos, AttackType attackType, float direction)	//111
{
	bool flag = false;
	if (true)
	{
		//this->initWithFile("bullet.png");
		_owner = owner;
		_power = power;
		_speed = speed;
		_distance = distance;
		_initialPosition = pos;
		this->setPosition(pos);
		_attackType = attackType;
		_direction = direction;
		this->setRotation(direction);
		flag = true;
	}
	return flag;
}

void *Arrow::getOwner()
{
	return _owner;
}

void Arrow::update(float dt)
{

}