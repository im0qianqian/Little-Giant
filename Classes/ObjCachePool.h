#ifndef __OBJ_CACHE_POOL_H__
#define __OBJ_CACHE_POOL_H__

#include "cocos2d.h"
#include <mutex>
using namespace std;
USING_NS_CC;

template<typename T>
class ObjCachePool
{
public:
	ObjCachePool();
	ObjCachePool(const ObjCachePool<T> &x);
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
	std::deque<T* > _cachePool;	//�����
	mutex _lock;				//ͬ����
	int _cacheSize;				//����ش�С
	Node * _layer;				//����������õ�ͼ��
};

template<typename T>
ObjCachePool<T>::ObjCachePool() :
	_cacheSize(0),
	_layer(nullptr),
	_cachePool(std::deque<T* >())
{
	
}

template<typename T>
ObjCachePool<T>::ObjCachePool(const ObjCachePool<T>& x)
{
	/* �������캯����ֱ�Ӵ�ֵ���ݶ� */
	_cachePool = x._cachePool;
	_lock = x._lock;
	_cacheSize = x._cacheSize;
	_layer = x._layer;
}

template<typename T>
ObjCachePool<T>::ObjCachePool(Node * const & node, const int & size) :
	_cacheSize(size),
	_layer(node),
	_cachePool(std::deque<T* >())
{
}


template<typename T>
ObjCachePool<T>::~ObjCachePool()
{
}

template<typename T>
void ObjCachePool<T>::addToPool(T* const & t)
{
	if (t == nullptr)return;
	/*
	* ��ӵ��������ζ�ŵ�ǰ����Ҫ����ҿ���������������������������λ��
	*/
	t->setVisible(false);
	t->setPosition3D(-Vec3::UNIT_Y * 10);
	t->syncNodeToPhysics();

	cout << "add " << t->Node::getTag() << "\t\t\t\t\t" << t << endl;
	_lock.lock();
	_cachePool.push_back(t);
	if(t->Node::getTag()==2)
		cout << "���������ʣ�ࣺ\t\t\t" << _cachePool.size() << endl;
	_lock.unlock();
}

template<typename T>
void ObjCachePool<T>::createCachePool()
{
	//��������
	_lock.lock();
	_cachePool.clear();
	_lock.unlock();
	for (auto i = 0; i < _cacheSize; i++)
	{
		auto t = T::create();
		CCASSERT(t, "NULL");
		if (t != nullptr)
		{
			cout << "create " << t->Node::getTag() << "\t" << t << endl;
			_layer->addChild(t);
			addToPool(t);
		}
	}
	//cout << "����ش����ɹ�����С��" << _cachePool.size() << endl;
}

template<typename T>
T* ObjCachePool<T>::getFromPool()
{
	T* t = nullptr;
	_lock.lock();
	if (!_cachePool.empty())
	{
		t = _cachePool.front();
		_cachePool.pop_front();
	}
	_lock.unlock();
	/*
	* �ӻ������ȡ��������ζ�Ÿö���Ҫ����ʾ������
	*/
	//CCASSERT(t, "NULL");
	if (t != nullptr)
	{
		cout << "get " << t->Node::getTag() << " " << t << endl;
		t->setVisible(true);
		//cout << "�ɹ�ȡ��һ������"<<t<<"\t���������ʣ�ࣺ"<<_cachePool.size() << endl;
	}
	return t;
}

#endif
