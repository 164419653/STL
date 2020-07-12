#pragma once

#include"Stack.h"
#include"Exception.h"

namespace JYLib
{

template <typename T,int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;
public:
public:
    StaticStack()
    {
        m_top = -1;
        m_size = 0;
    }

    void push(const T& e)
    {
        if(m_size < N)
        {
            m_space[m_top+1] = e;
            m_top++;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no space to push ...");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_size--;
            m_top--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The StaticStack has no elements...");
        }
    }

    T top() const
    {
        if(m_size > 0)
        {
            return m_space[m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The StaticStack has no elements...");
        }
    }

    void clear()
    {
        m_size = 0;
        m_top = -1;
    }

    int size() const
    {
        return m_size;
    }

    int capacity() const
    {
        return N;
    }
};
}
