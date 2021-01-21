﻿#ifndef __OBJ_CACHE_POOL_H__
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
	/* 添加一个对象到缓存池 */
	void addToPool(T* const &t);
	/* 创建缓存池 */
	void createCachePool();
	/* 设置缓存池大小 */
	void setCacheSize(const int &size) { _cacheSize = size; }
	/* 获取缓存池大小 */
	int getCacheSize() { return _cacheSize; }
	/* 设置图层 */
	void setLayer(Node *const &node) { _layer = node; }
	/* 获取当前图层 */
	void getLayer() { return _layer; }
	/* 获取缓存池剩余容量 */
	int getResidualSize() { return _cachePool.size(); }
	/* 获取一个对象指针 */
	T* getFromPool();
private:
	std::deque<T* > _cachePool;	//缓冲池
	mutex _lock;				//同步锁
	int _cacheSize;				//缓冲池大小
	Node * _layer;				//缓冲池所作用的图层
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
	/* 拷贝构造函数，直接传值，暂定 */
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
	* 添加到缓存池意味着当前对象要让玩家看不见，于是在这里设置了它的位置
	*/
	t->setVisible(false);
	t->setPosition3D(-Vec3::UNIT_Y * 10);
	t->syncNodeToPhysics();

	_lock.lock();
	_cachePool.push_back(t);
	_lock.unlock();
}

template<typename T>
void ObjCachePool<T>::createCachePool()
{
	//缓存池清空
	_lock.lock();
	_cachePool.clear();
	_lock.unlock();
	for (auto i = 0; i < _cacheSize; i++)
	{
		auto t = T::create();
		CCASSERT(t, "NULL");
		if (t != nullptr)
		{
			_layer->addChild(t);
			addToPool(t);
		}
	}
	//cout << "缓存池创建成功，大小：" << _cachePool.size() << endl;
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
	* 从缓存池中取出对象意味着该对象要被显示出来了
	*/
	//CCASSERT(t, "NULL");
	if (t != nullptr)
	{
		t->setVisible(true);
		//cout << "成功取出一个对象："<<t<<"\t缓存池容量剩余："<<_cachePool.size() << endl;
	}
	return t;
}

#endif
