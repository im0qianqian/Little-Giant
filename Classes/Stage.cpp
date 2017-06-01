#include "Stage.h"
#include "Global.h"

Stage::Stage()
{
	// ���ñ�ǩΪ��������
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
		// ���ñ�ǩΪ��ǰ�������ָ�룬��Ϊ����ײ�������Ҫʹ��
		obj->setUserData(ret);

		ret->_physicsComponent = Physics3DComponent::create(obj);
		ret->addComponent(ret->_physicsComponent);
		ret->_contentSize = ret->getBoundingBox().size;
		ret->setTexture(texture);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}
