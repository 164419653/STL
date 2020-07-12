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
		virtual bool insert(const T& e) = 0;  // һ�����麯���еĺ���Ҫôʵ����ҪôҲ����Ϊ���麯������Ȼ�������������ʱ����������
		virtual bool insert(int i, const T& e) = 0;
		virtual bool remove(int i) = 0;
		virtual bool set(int i, const T& e) = 0;
		virtual bool get(int i, T& e) const = 0;
		virtual int find(const T& e) const = 0;
		virtual int length() const = 0;
		virtual void clear() = 0;
	};
}