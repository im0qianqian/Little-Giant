#ifndef __OBJ_CACHE_POOL_H__
#define __OBJ_CACHE_POOL_H__

#include "cocos2d.h"
USING_NS_CC;

template<typename T>
class ObjCachePool
{
public:
	ObjCachePool();
	ObjCachePool(Node *const &node, const int &size);
	~ObjCachePool();
	/* ���һ�����󵽻���� */
	void addToPool(T* const &t);
	/* ��������� */
	void createCachePool();
	/* ���û���ش�С */
	void setCacheSize(const int &size) { _cacheSize = size; }
	/* ��ȡ����ش�С */
	int getCacheSize() { return _cacheSize; }
	/* ����ͼ�� */
	void setLayer(Node *const &node) { _layer = node; }
	/* ��ȡ��ǰͼ�� */
	void getLayer() { return _layer; }
	/* ��ȡ�����ʣ������ */
	int getResidualSize() { return _cachePool.size(); }
	/* ��ȡһ������ָ�� */
	T* getFromPool();
private:
	Vector<T*> _cachePool;		//�����
	int _cacheSize;				//����ش�С
	Node * _layer;				//����������õ�ͼ��
};

template<typename T>
ObjCachePool<T>::ObjCachePool() :
	_cacheSize(0),
	_layer(nullptr)
{
	_cachePool.clear();
}

template<typename T>
ObjCachePool<T>::ObjCachePool(Node * const & node, const int & size):
	_cacheSize(size),
	_layer(node)
{
	_cachePool.clear();
}


template<typename T>
ObjCachePool<T>::~ObjCachePool()
{

}

template<typename T>
void ObjCachePool<T>::addToPool(T* const & t)
{
	/*
	 * ��ӵ��������ζ�ŵ�ǰ����Ҫ����ҿ���������������������������λ��
	 */
	t->setVisible(false);
	t->setPosition3D(-Vec3::UNIT_Y * 10);
	t->syncNodeToPhysics();

	_cachePool.pushBack(t);
	cout << "���������ʣ�ࣺ" << _cachePool.size() << endl;
}

template<typename T>
void ObjCachePool<T>::createCachePool()
{
	//��������
	_cachePool.clear();
	for (auto i = 0; i < _cacheSize; i++)
	{
		auto t = T::create();
		_layer->addChild(t);
		addToPool(t);
	}
	cout << "����ش����ɹ�����С��" << _cachePool.size() << endl;
}

template<typename T>
T* ObjCachePool<T>::getFromPool()
{
	T* t = nullptr;
	if (!_cachePool.empty())
	{
		t = _cachePool.back();
		_cachePool.popBack();
		/*
		 * �ӻ������ȡ��������ζ�Ÿö���Ҫ����ʾ������
		 */
		t->setVisible(true);
	}
	cout << "�ɹ�ȡ��һ������"<<t<<"\t���������ʣ�ࣺ"<<_cachePool.size() << endl;
	return t;
}

#endif