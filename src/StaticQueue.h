#pragma once

#include"Queue.h"
#include"Exception.h"

namespace JYLib
{

template <typename T,int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_size;

public:
    StaticQueue()
    {
        m_front = 0;
        m_rear = 0;
        m_size = 0;
    }

    void add(const T& e)
    {
        if(m_size < N)
        {
            m_space[m_rear] = e;
            m_rear = (m_rear+1) % N;
            m_size++;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The StaticQueue is full ...");
        }
    }

    void remove()
    {
        if(m_size > 0)
        {
            m_front = (m_front+1) % N;
            m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The StaticQueue is NULL ...");
        }
    }

    T front() const
    {
        if(m_size > 0)
        {
            return m_space[m_front];
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The StaticQueue is NULL ...");
        }
    }

    void clear()
    {
        m_size = 0;
        m_front = 0;
        m_rear = 0;
    }

    int length() const
    {
        return m_size;
    }

    int capacity() const
    {
        return N;
    }
};

}
