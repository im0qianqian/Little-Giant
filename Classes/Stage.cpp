#include "Stage.h"
#include "Global.h"

Stage::Stage()
{
	// 设置标签为固体属性
	setTag(kGlobalStage);
}

Stage::~Stage()
{

}

bool Stage::init()
{
	return true;
}

Stage* Stage::create(Physics3DRigidBodyDes *rbDes, const std::string &ptr, const std::string &texture)
{
	auto ret = new Stage();
	if (ret && ret->initWithFile(ptr) && ret->init())
	{
		auto obj = Physics3DRigidBody::create(rbDes);
		// 设置标签为当前固体对象指针，因为在碰撞检测中需要使用
		obj->setUserData(ret);
		ret->_physicsComponent = Physics3DComponent::create(obj);
		ret->addComponent(ret->_physicsComponent);
		//ret->_contentSize = ret->getBoundingBox().size;
		ret->setTexture(texture);
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}
	return ret;
}
