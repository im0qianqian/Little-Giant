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
	loadLabel = Label::create("Loading:", "arial", 30);
	loadLabel->setPosition(Point(visibleSize.width / 2 - 30, visibleSize.height / 2 + 30));
	this->addChild(loadLabel,1);

	percentLabel = Label::create("       0%", "arial", 30);
	CCLOG("####%d %d", visibleSize.width / 2, visibleSize.height / 2);
	percentLabel->setPosition(Point(visibleSize.width / 2 + 35, visibleSize.height / 2 + 30));
	this->addChild(percentLabel, 2);
	
	totalImage = 500;
	loadImage = 0;

	CCLOG("PASS1");

	timer = ProgressTimer::create(Sprite::create("blood.png"));
	timer->setType(cocos2d::ProgressTimer::Type::BAR);
	timer->setMidpoint(Vec2(0, 1));
	timer->setBarChangeRate(Vec2(1, 0));
	timer->setPercentage(0.0f);
	timer->setScaleX(2);
	//timer->setScale(2);
	CCLOG("####%d %d", visibleSize.width / 2, visibleSize.height / 2);
	timer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(timer,3);

	CCLOG("PASS2");

	for (int i = 1; i <= 500; i++)
	{
		CCLOG("PASS3,%d",i);
		Director::getInstance()->getTextureCache()->addImageAsync("HelloWorld.png", CC_CALLBACK_1(LoadLayer::LoadingCallback,this));
	}
	/*for (int i = 1; i <= 500; i++)
	{
		CCLOG("#########" + i);
		LoadLayer::LoadingCallback();
	}*/
	return true;

}

void LoadLayer::LoadingCallback(Ref *pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	loadImage++;
	float newPercent = 100 - ((float)totalImage - (float)loadImage) / ((float)totalImage / 100);
	timer->setPercentage(newPercent);
	CCLOG("%f", newPercent);
	char buf_str[16];
	sprintf(buf_str, "       %d%%", (int)(((float)loadImage) / (float)totalImage * 100));
	CCLOG("%s", buf_str);
	percentLabel->setString(buf_str);
	if (loadImage == totalImage)
	{
		CCLOG("PASS4");
		this->removeChild(timer);
		this->removeChild(percentLabel);
		this->removeChild(loadLabel);
		CCLOG("PASS5");
		/*Sprite *newScene = Sprite::create("background.png");
		CCLOG("PASS6");
		this->addChild(newScene);
		CCLOG("PASS7");*/
		SceneManager::getInstance()->changeScene(kGameScene);
		CCLOG("PASS8");
	}
}

