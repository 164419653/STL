#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include"LinkList.h"

namespace JYLib
{

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    Node* last() const
    {
        return this->position(this->m_length);
    }

    void last_to_first()
    {
        last()->next = this->m_head.next;
    }

    int mod(int i)
    {
        return (this->m_length==0?0:i%this->m_length);
    }

public:
    bool insert(const T& e)
    {
        return insert(this->m_length,e);
    }

    bool insert(int i,const T& e)
    {
        bool ret = true;

        i = (i % (this->m_length + 1));
        ret = LinkList<T>::insert(i,e);

        if(ret && i==0)
        {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i)
    {
        bool ret = true;

        i = mod(i);

        if(i == 0)
        {
            Node* toDel = this->m_head.next;
            if(toDel != NULL)
            {
                this->m_head.next = toDel->next;
                this->m_length--;
                if(this->m_length > 0)
                {
                    last_to_first();
                    if(this->m_current == toDel)
                    {
                        this->m_current = toDel->next;
                    }
                }
                else
                {
                    this->m_head.next = NULL;
                    this->m_current = NULL;
                }
            }
            else
            {
                ret = false;
            }
            this->destroy(toDel);
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i,T& e)
    {
        return LinkList<T>::set(mod(i),e);
    }

    bool get(int i,T& e)
    {
        return LinkList<T>::get(mod(i),e);
    }

    T get(int i) const
    {
        T e;
        get(mod(i),e);
        return e;
    }

    int find(const T& e)
    {
        int ret = -1;

        Node* slider = this->m_head.next;
        for(int i=0;i<this->m_length;i++)
        {
            if(slider->value == e)
            {
                ret = i;
                break;
            }
            slider = slider->next;
        }

        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)
        {
            remove(1);
        }

        if(this->m_length == 1)
        {
            Node* toDel = this->m_head.next;

            this->m_length = 0;
            this->m_head.next = NULL;
            this->m_current = NULL;

            this->destroy(toDel);
        }
    }

    bool move(int i,int step=1)
    {
        return LinkList<T>::move(mod(i),step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);
    }

    ~CircleList()
    {
        clear();
    }
};


}



#endif // CIRCLELIST_H
