#include "LoadLayer.h"
#include "SceneManager.h"
LoadLayer::LoadLayer()
{

}
LoadLayer::~LoadLayer()
{

}

bool LoadLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *cloud = Sprite::create("cloud.png");
	cloud->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2+65));
	this->addChild(cloud);
	_loadLabel = Label::create("Loading:", "arial", 30);
	_loadLabel->setPosition(Point(visibleSize.width / 2 - 30, visibleSize.height / 2 + 30));
	this->addChild(_loadLabel,1);
	_percentLabel = Label::create("       0%", "arial", 30);
	_percentLabel->setPosition(Point(visibleSize.width / 2 + 35, visibleSize.height / 2 + 30));
	this->addChild(_percentLabel, 2);
	
	_totalImage = 500;
	_loadImage = 0;

	_timer = ProgressTimer::create(Sprite::create("load.png"));

	_timer->setType(cocos2d::ProgressTimer::Type::BAR);
	_timer->setMidpoint(Vec2(0, 1));
	_timer->setBarChangeRate(Vec2(1, 0));
	_timer->setPercentage(0.0f);

	_timer->setScaleX(2);
	_timer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_timer,3);

	for (int i = 1; i <= 500; i++)
	{
		Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png", CC_CALLBACK_0(LoadLayer::loadingCallback,this));
	}
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
	return true;

}

void LoadLayer::loadingCallback()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_loadImage++;
	float newPercent = 100 - ((float)_totalImage - (float)_loadImage) / ((float)_totalImage / 100);
	_timer->setPercentage(newPercent);
	char buf_str[16];
	sprintf(buf_str, "       %d%%", (int)(((float)_loadImage) / (float)_totalImage * 100));
	_percentLabel->setString(buf_str);
	if (_loadImage == _totalImage)
	{
		this->removeChild(_timer);
		this->removeChild(_percentLabel);
		this->removeChild(_loadLabel);
		SceneManager::getInstance()->changeScene(kGameScene);
	}
}

