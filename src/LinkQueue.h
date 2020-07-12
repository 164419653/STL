#pragma once

#include"Queue.h"
#include"Exception.h"
#include"LinkList.h"

namespace JYLib
{

template <typename T>
class LinkQueue : public Object
{
protected:
    LinkList<T> m_list;
public:

    void add(const T& e)
    {
        m_list.insert(e);
    }

    void remove()
    {
        if(m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The LinkQueue is NULL ...");
        }
    }

    T front() const
    {
        if(m_list.length() > 0)
        {
            return m_list.get(0);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The LinkQueue is NULL ...");
        }
    }

    void clear()
    {
        m_list.clear();
    }

    int length() const
    {
        return  m_list.length();
    }
};

}
