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
	//���ҡ�˱���ͼ  
	Sprite* spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setPosition(pos);
	addChild(spRockerBG, 0, kRockerBG);
	//���ҡ���Ϸ��Ǹ����ƶ���ͼ  
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setPosition(pos);
	addChild(spRocker, 1, kRocker);
	spRocker->setOpacity(180);
	//ҡ�˱���ͼ����  
	_rockerBGPosition = pos;
	//ҡ�˱���ͼ�뾶  
	_rockerBGR = spRockerBG->getContentSize().width*0.5f;
	// �󶨼����¼�
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBegan, this);
	_listener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMoved, this);
	_listener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_listener, this);
}

//�õ�������ĽǶ�ֵ  
float Rocker::getRad(const Vec2 &pos1, const Vec2 &pos2)
{
	//�õ����������x,y����ֵ  
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//������߳���  
	float x = px2 - px1;
	float y = py1 - py2;
	//����   ��  ���η� ��ʽ  
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / xie;
	//�����Ҷ���֪�����߳���Ƕȣ�cos = �ڱ�/б��  
	float rad = acos(cos);
	//������Y���� <ҡ�˵�Y����ʱ��ȡ��ֵ  
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
//�õ���Ƕȶ�Ӧ�İ뾶Ϊr��Բ��һ�����  
Vec2 Rocker::getAnglePosition(const float &r, const float &angle)
{
	return Vec2(r*cos(angle), r*sin(angle));
}

bool Rocker::onTouchBegan(Touch* const &touch, Event* const &event)
{
	Sprite* sp = (Sprite*)getChildByTag(kRocker);
	//�õ�����������  
	Vec2 point = touch->getLocation();
	//�ж��Ƿ�����sp������飺boundingBox()�����С֮�ڵ��������� 
	if (sp->getBoundingBox().containsPoint(point))
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
	//�ж�����Բ�ĵľ����Ƿ����ҡ�˱����İ뾶  
	if (sqrt(pow(point.x - _rockerBGPosition.x, 2) + pow(point.y - _rockerBGPosition.y, 2)) >= _rockerBGR)
	{
		//�õ�������ҡ�˱���Բ���γɵĽǶ�  
		float angle = getRad(_rockerBGPosition, point);
		//ȷ��СԲ�˶���Χ�ڱ���Բ��
		sp->setPosition(getAnglePosition(_rockerBGR, angle)+ Vec2(_rockerBGPosition.x, _rockerBGPosition.y));
	}
	else {
		//�����ڱ���Բ������津���˶�  
		sp->setPosition(point);
	}
	// ��������������ͼ��
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
	rocker->runAction(MoveTo::create(0.08f, rockerBG->getPosition()));
	_isCanMove = false;
	// ��������������ͼ��
	event->stopPropagation();
}