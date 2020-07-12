#pragma once

#include<cstdlib>
#include"Pointer.h"
#include"Exception.h"

namespace JYLib
{
	template<typename T>
	class SharedPointer : public Pointer<T>
	{
	protected:
		int *m_ref;

		void assign(const SharedPointer<T>& obj)
		{
			this->m_pointer = obj.m_pointer;
			this->m_ref = obj.m_ref;

            if (this->m_pointer)
			{
				(*(this->m_ref))++;
			}
		}
	public:
		SharedPointer(T* p = NULL)
		{
			this->m_ref = NULL;
			this->m_pointer = NULL;
			if (p)
			{
				this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
				if (this->m_ref)
				{
					*(this->m_ref) = 1;
					this->m_pointer = p;
				}
				else
				{
					THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to make a int variable...");
				}
			}
		}

        SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(NULL)
        {
			assign(obj);
		}

		SharedPointer<T>& operator= (const SharedPointer<T>& obj)
		{
			if (this != &obj)
			{
				clear();
				assign(obj);
			}

			return *this;
		}

		void clear()
		{
			T* todel = this->m_pointer;
			int* ref = this->m_ref;

			this->m_pointer = NULL;
			this->m_ref = NULL;

            if (todel)
			{
				(*ref)--;
				if (*ref <= 0)
				{
					free(ref);
					delete todel;
				}
			}
		}

		~SharedPointer()
		{
			clear();
		}
	};

    template <typename T>
    bool operator==(const SharedPointer<T>& l,SharedPointer<T>& r)
    {
        return (l.get() == r.get());
    }

    template <typename T>
    bool operator!=(const SharedPointer<T>& l,SharedPointer<T>& r)
    {
        return !(l == r);
    }

}
