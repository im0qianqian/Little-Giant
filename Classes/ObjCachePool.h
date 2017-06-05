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
	/* ���һ�����󵽻���� */
	void addToPool(T* const &t);
	/* ��������� */
	void createCachePool();
	/* ���û���ش�С */
	void setCacheSize(const int &size);
	/* ��ȡһ������ָ�� */
	T* getFromPool();
private:
	Vector<T*> _cachePool;		//�����
	int _cacheSize;				//����ش�С
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
		_cachePool.pushBack(t);
	}
	cout << "����ش����ɹ�����С��" << _cachePool.size() << endl;
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
	cout << "�ɹ�ȡ��һ������"<<t<<"\t���������ʣ�ࣺ"<<_cachePool.size() << endl;
	return t;
}

#endif