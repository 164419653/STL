#pragma once

#include "SeqList.h"
#include "Exception.h"

namespace JYLib
{
	template<typename T>
	class DynamicList : public SeqList<T>
	{
	protected:
		int m_capacity;
	
	public:
		DynamicList(int capacity)
		{
			this->m_capacity = capacity;
            this->m_array = new T[capacity];
            if (this->m_array != NULL)
			{
				this->m_length = 0;
				this->m_capacity = capacity;
			}
			else
			{
				THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory !");
			}
		}

		int capacity() const
		{
			return m_capacity;
		}

		void resize(int capacity)
		{
			if (this->m_capacity != capacity)
			{
				T* array = new T[capacity];
				if (array != NULL)
				{
                    int len = (this->m_length < capacity) ? this->m_length : capacity;
					for (int i = 0; i < len; i++)
					{
                        array[i] = this->m_array[i];
					}

                    T* tmp = this->m_array;  // 为了防止 delete 是可能触发的异常

                    this->m_array = array;
                    this->m_length = len;
					m_capacity = capacity;
					
					delete[]tmp;
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory !");
				}
			}
		}

		~DynamicList()
		{
            delete[] this->m_array;
		}

	};

}
