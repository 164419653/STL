#pragma once

#include"Object.h"

namespace JYLib
{
	template<typename T>
	class List : public Object
	{
	protected:
		List(const List<T> &obj);
		List<T>& operator =(const List<T> &obj);
	public:
		List() {}
		virtual bool insert(const T& e) = 0;  // 一个纯虚函数中的函数要么实现了要么也定义为纯虚函数，不然调用这个函数的时候会出现问题
		virtual bool insert(int i, const T& e) = 0;
		virtual bool remove(int i) = 0;
		virtual bool set(int i, const T& e) = 0;
		virtual bool get(int i, T& e) const = 0;
		virtual int find(const T& e) const = 0;
		virtual int length() const = 0;
		virtual void clear() = 0;
	};
}