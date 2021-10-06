#pragma once

#include "LinkList.h"

namespace JYLib
{

    template< typename T, int N >
    class StaticLinkList : public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;  // 即使父类已经存在了node类型但是这个node是模板类型

        struct SNode : public Node
        {
            void* operator new(unsigned int size, void* loc)
            {
                (void)size;
                return loc;
            }
        };

        unsigned char m_space[sizeof(SNode) * N];
        int m_used[N];

        Node* create()
        {
            SNode* ret = NULL;

            for (int i = 0; i < N; i++)
            {
                if (!m_used[i])
                {
                    ret = reinterpret_cast<SNode*>(m_space) + i;
                    ret = new(ret)SNode();
                    m_used[i] = 1;
                    break;
                }
            }

            return ret;
        }

        void destroy(Node* pn)
        {
            SNode* space = reinterpret_cast<SNode*>(m_space);
            SNode* psn = dynamic_cast<SNode*>(pn);

            for (int i = 0; i < N; i++)
            {
                if (psn == (space + i))
                {
                    m_used[i] = 0;
                    psn->~SNode();
                    break;
                }
            }
        }
    public:
        StaticLinkList()
        {
            for (int i = 0; i < N; i++)
            {
                m_used[i] = 0;
            }
        }

        int capacity()
        {
            return N;
        }

        ~StaticLinkList()
        {
            this->m_header.next = NULL;
        }
    };

}