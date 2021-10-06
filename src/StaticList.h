#pragma once


#include "SeqList.h"

namespace JYLib
{

    template < typename T, int N >
    class StaticList : public SeqList<T>
    {
    protected:
        T m_space[N];    // 顺序存储空间， N 为模板参数
    public:
        StaticList()    // 指定父类成员的具体值
        {
            this->m_array = m_space;
            this->m_length = 0;
        }

        int capacity() const
        {
            return N;
        }
    };


}