#pragma once

#include "List.h"
#include "Exception.h"

namespace JYLib
{
	template <typename T>
	class SeqList : public List<T>
	{
	protected:
		T* m_array;
		int m_length;

	public:

		virtual bool insert(const T& e)
		{
			return insert(m_length, e);
		}

		bool insert(int i, const T& e)
		{
			bool ret = ((i >= 0) && (i <= m_length));
			ret = (ret && (m_length < capacity()));  // 等式右边需要加上ret，不然上一行的结果就没有保存

			if (ret)
			{
				for (int p = m_length; p > i; --p)
				{
					m_array[p] = m_array[p - 1];
				}
				m_array[i] = e;
				++m_length;
			}

			return ret;
		}
		bool remove(int i)
		{
			bool ret = ((i < m_length) && (i >= 0));
			
			if (ret)
			{
				for (; i < m_length; ++i)
				{
					m_array[i] = m_array[i + 1];
				}
				--m_length;
			}

			return ret;
		}

		bool set(int i, const T& e)
		{
			bool ret = ((i >= 0) && (i < m_length));
			
			if (ret)
			{
				m_array[i] = e;
			}

			return ret;
		}

		bool get(int i, T& e) const
		{
			bool ret = ((i >= 0) && (i < m_length));

			if (ret)
			{
				e = m_array[i];
			}

			return ret;
		}

		int find(const T& e) const
		{
			int ret = -1;

			for (int i = 0; i < m_length; i++)
			{
				if (m_array[i] == e)
				{
					ret = i;
					break;
				}
			}

			return ret;
		}

		int length() const
		{
			return m_length;
		}

		void clear()
		{
			m_length = 0;
		}

		T& operator[] (int i)
		{
			bool ret = ((i >= 0) && (i < m_length));

			if (ret)
			{
				return m_array[i];
			}
			else
			{
				THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is not valid ...");
			}
		}
		T operator[] (int i) const
		{
            return (const_cast<SeqList<T>&>(*this))[i];
			// 上一行代码的优点：1.避免了代码冗余  2.强制类型转换为引用，避免了拷贝带来的开销
		}

		virtual int capacity() const = 0;
	};
}
