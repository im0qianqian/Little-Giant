#ifndef __OBJ_CACHE_POOL_H__
#define __OBJ_CACHE_POOL_H__

#include "cocos2d.h"
USING_NS_CC;

template<typename T>
class ObjCachePool
{
public:
	ObjCachePool();
	~ObjCachePool();
	/* 添加一个对象到缓存池 */
	void addToPool(T* const &t);
	/* 创建缓存池 */
	void createCachePool();
	/* 设置缓存池大小 */
	void setCacheSize(const int &size);
	/* 获取一个对象指针 */
	T* getFromPool();
private:
	Vector<T*> _cachePool;		//缓冲池
	int _cacheSize;				//缓冲池大小
};

template<typename T>
ObjCachePool<T>::ObjCachePool() :
	_cacheSize(0)
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
	_cachePool.pushBack(t);
	cout << "缓存池容量剩余：" << _cachePool.size() << endl;
}

template<typename T>
void ObjCachePool<T>::createCachePool()
{
	//缓存池清空
	_cachePool.clear();
	for (auto i = 0; i < _cacheSize; i++)
	{
		auto t = T::create();
		_cachePool.pushBack(t);
	}
	cout << "缓存池创建成功，大小：" << _cachePool.size() << endl;
}

template<typename T>
void ObjCachePool<T>::setCacheSize(const int & size)
{
	_cacheSize = size;
}

template<typename T>
T* ObjCachePool<T>::getFromPool()
{
	T* t = nullptr;
	if (!_cachePool.empty())
	{
		t = _cachePool.back();
		_cachePool.popBack();
	}
	cout << "成功取出一个对象："<<t<<"\t缓存池容量剩余："<<_cachePool.size() << endl;
	return t;
}

#endif