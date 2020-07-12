#pragma once

#include"DualLinkList.h"

namespace JYLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{

protected:

    typedef typename DualLinkList<T>::Node Node;

    int mod(int i)
    {
        return this->m_length==0?0:i%this->m_length;
    }

public:
    DualCircleList()
    {
        this->m_head.next = reinterpret_cast<Node*>(&(this->m_head));
        this->m_head.pre = reinterpret_cast<Node*>(&(this->m_head));
        this->m_length = 0;
        this->m_step = 1;
        this->m_current = NULL;
    }


    bool insert(int i, const T& e)
    {
        bool ret = true;
        i = i % (this->m_length+1);

        Node* node = this->create();
        if (node != NULL)
        {
            Node* current = this->position(i);
            Node* next = current->next;

            node->value = e;
            current->next = node;
            node->next = next;
            next->pre = node;
            node->pre = current;

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "no memory to create new node for LinkList...");
        }
        return ret;
    }

    bool remove(int i)
    {
        bool ret = (this->m_length > 0);

        i = mod(i);
        if (ret)
        {
            Node* current = this->position(i);
            Node* delNode = current->next;
            Node* next = delNode->next;

            current->next = next;
            next->pre = current;

            this->m_length--;
            this->destroy(delNode);

        }

        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = (this->m_length > 0);

        if (ret)
        {
            i = i % this->m_length+1;
            this->position(i)->value = e;
        }

        return ret;
    }

    virtual bool get(int i, T& e) const
    {
        bool ret = (this->m_length > 0);

        if (ret)
        {
            i = i % this->m_length+1;
            e = this->position(i)->value;
        }

        return ret;
    }

    virtual T get(int i)
    {
        T ret;

        if (get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "The DualCircleList has no elements...");
        }
        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        Node* cur = this->m_head.next;
        int i = 0;
        while (cur != reinterpret_cast<Node*>(&(this->m_head)))
        {
            if (cur->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                i++;
                cur = cur->next;
            }
        }

        return ret;
    }



    virtual bool move(int i, int step = 1)
    {
        i = i % (this->m_length);
        bool ret =(step > 0);

        if (ret)
        {
            this->m_current = this->position(i)->next;
            this->m_step = step;
        }

        return ret;
    }

    virtual bool end()
    {
        return ((this->m_current == reinterpret_cast<Node*>(&(this->m_head))) || (this->m_current == NULL));
    }

    virtual T current()
    {
        if (!end())
        {
            return this->m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }

    virtual bool next()
    {
        int i = 0;
        while ((i < this->m_step) && (!end()))
        {
            this->m_current = this->m_current->next;
            i++;
        }

        return (i == this->m_step);
    }

    virtual bool pre()
    {
        int i = 0;
        while ((i < this->m_step) && (!end()))
        {
            this->m_current = this->m_current->pre;
            i++;
        }

        return (i == this->m_step);
    }

    ~DualCircleList()
    {
        this->clear();
    }
};

}
