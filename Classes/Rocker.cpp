#include "Rocker.h"
#include "Global.h"

Rocker * Rocker::create(const std::string & rockerImageName, const std::string & rockerBGImageName, const Vec2 & pos)
{
	auto rocker = Rocker::create();
	CCASSERT(rocker, "NULL");
	if (rocker != nullptr)
	{
		rocker->rockerInit(rockerImageName, rockerBGImageName, pos);
		return rocker;
	}
	CC_SAFE_DELETE(rocker);
	return nullptr;
}

void Rocker::rockerInit(const std::string & rockerImageName, const std::string & rockerBGImageName, const Vec2 & pos)
{
	//添加摇杆背景图  
	Sprite* spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(pos);
	addChild(spRockerBG, 0, kRockerBG);
	//添加摇杆上方那个可移动的图  
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setPosition(pos);
	addChild(spRocker, 1, kRocker);
	spRocker->setOpacity(180);
	//摇杆背景图坐标  
	_rockerBGPosition = pos;
	//摇杆背景图半径  
	_rockerBGR = spRockerBG->getContentSize().width*0.5;
	// 绑定监听事件
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBegan, this);
	_listener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMoved, this);
	_listener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}

//得到两坐标的角度值  
float Rocker::getRad(const Vec2 &pos1, const Vec2 &pos2)
{
	//得到两点的坐标x,y坐标值  
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//求出两边长度  
	float x = px2 - px1;
	float y = py1 - py2;
	//开方   与  几次方 公式  
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / xie;
	//反余弦定理，知道两边长求角度：cos = 邻边/斜边  
	float rad = acos(cos);
	//当触屏Y坐标 <摇杆的Y坐标时，取反值  
	if (py1 > py2)
	{
		rad = -rad;
	}
	return rad;
}
Vec2 Rocker::getDirection() const
{
	return getChildByTag(kRocker)->getPosition() - _rockerBGPosition;
}
//得到与角度对应的半径为r的圆上一坐标点  
Vec2 Rocker::getAnglePosition(const float &r, const float &angle)
{
	return Vec2(r*cos(angle), r*sin(angle));
}

bool Rocker::onTouchBegan(Touch* const &touch, Event* const &event)
{
	Sprite* sp = (Sprite*)getChildByTag(kRocker);
	//得到触屏点坐标  
	Vec2 point = touch->getLocation();
	//判断是否点击到sp这个精灵：boundingBox()精灵大小之内的所有坐标 
	if (sp->boundingBox().containsPoint(point))
	{
		_isCanMove = true;
	}
	return true;
}

void Rocker::onTouchMoved(Touch* const &touch, Event* const &event)
{
	if (!_isCanMove)
	{
		return;
	}
	Sprite* sp = (Sprite*)getChildByTag(kRocker);
	Vec2 point = touch->getLocation();
	//判断两个圆心的距离是否大于摇杆背景的半径  
	if (sqrt(pow(point.x - _rockerBGPosition.x, 2) + pow(point.y - _rockerBGPosition.y, 2)) >= _rockerBGR)
	{
		//得到触点与摇杆背景圆心形成的角度  
		float angle = getRad(_rockerBGPosition, point);
		//确保小圆运动范围在背景圆内
		sp->setPosition(ccpAdd(getAnglePosition(_rockerBGR, angle), ccp(_rockerBGPosition.x, _rockerBGPosition.y)));
	}
	else {
		//触点在背景圆内则跟随触点运动  
		sp->setPosition(point);
	}
	// 操作不传向其他图层
	event->stopPropagation();
}

void Rocker::onTouchEnded(Touch* const &touch, Event* const &event)
{
	if (!_isCanMove)
	{
		return;
	}
	Sprite* rocker = (Sprite*)getChildByTag(kRocker);
	Sprite* rockerBG = (Sprite*)getChildByTag(kRockerBG);
	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08, rockerBG->getPosition()));
	_isCanMove = false;
	// 操作不传向其他图层
	event->stopPropagation();
}