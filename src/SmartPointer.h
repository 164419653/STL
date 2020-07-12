#pragma once

#include"Pointer.h"

namespace JYLib
{

	template<typename T>
	class SmartPointer : public Pointer<T> 
	{

	public:
		SmartPointer(T* m_pointer = NULL): Pointer<T>(m_pointer)
		{
		}

		SmartPointer(const SmartPointer<T>& obj)
		{
			this->m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
		}


		SmartPointer<T>& operator = (const SmartPointer<T>& obj)
		{
			if (this != &obj)
			{
				T* temp = this->m_pointer;
				this->m_pointer = obj.m_pointer;
				const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
				delete temp;
			}
			return *this;
		}

		~SmartPointer()
		{
			delete this->m_pointer;
		}

	};

}

// 小总结 注意不要将 SmartPointer<T>& 写为 SmartPointer<T*>&