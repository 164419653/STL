#pragma once

#include<cstdlib>
#include"Object.h"

namespace JYLib
{
	template<typename T>
	class Pointer : public Object
	{
	protected:
		T* m_pointer;

	public:
		Pointer(T* p = NULL)
		{
			this->m_pointer = p;
		}

		T& operator *()
		{
            return (*m_pointer);
		}

		T* operator ->()
		{
			return this->m_pointer;
		}

        const T& operator *() const
        {
            return (*this);
        }

        const T* operator ->() const
        {
            return this->m_pointer;
        }

        bool isNull() const
		{
			return (this->m_pointer == NULL);
		}

        T* get() const
		{
			return m_pointer;
		}
	};
}
