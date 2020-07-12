#pragma once

#include"LinkList.h"

namespace JYLib
{
    template<typename T,int N>
    class StaticLinkList : public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;

        unsigned char m_space[sizeof(Node) * N];
        bool m_used[N];

        Node* create()
        {
            Node* ret = NULL;
            for (int i = 0; i < N; i++)
            {
                if (!m_used[i])
                {
                    ret = reinterpret_cast<Node*>(m_space) + i;
                    m_used[i] = true;
                    break;
                }
            }
            return ret;
        }

        void destroy(Node* pn)
        {
            Node* space = reinterpret_cast<Node*>(m_space);

            for (int i = 0; i < N; i++)
            {
                if (pn == (space + i))
                {
                    m_used[i] = false;
                    break;
                }
            }
        }

    public:
        StaticLinkList()
        {
            for (int i = 0; i < N; i++)
            {
                m_used[i] = false;
            }
        }

        ~StaticLinkList()
        {
            this->clear();
        }
    };
}
