#pragma once

#include"Tree.h"
#include"GTreeNode.h"
#include"Exception.h"
#include"LinkQueue.h"

#include<iostream>
using namespace std;

namespace JYLib
{

template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T>*> m_queue;

    GTreeNode<T>* find(GTreeNode<T>* node , const T& value)
    {
        GTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.move(0);((!node->child.end())&&(ret==NULL));node->child.next())
                {
                    ret = find(node->child.current(),value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node , GTreeNode<T>* obj)
    {
        GTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            return node;
        }
        else
        {
            if(node != NULL)
            {
                for(node->child.move(0);((!node->child.end())&&(ret==NULL));node->child.next())
                {
                    ret = find(node->child.current(),obj);
                }
            }
        }

        return ret;
    }

    void clear(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.move(0);!(node->child.end());node->child.next())
            {
                clear(node->child.current());
            }
            if(node->flag())
            {
                delete node;
            }
            else
            {
                cout<<node->value<<endl;
            }
        }
    }

    void remove(GTreeNode<T>* node,GTree<T>*& ret)
    {
        ret = new GTree<T>();
        if(ret != NULL)
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
                child.remove(child.find(node));
                node->parent = NULL;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory at remove ...");
        }
        ret->m_root = node;
    }

    int count(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = 1;
            for(node->child.move(0);!node->child.end();node->child.next())
            {
                ret += count(node->child.current());
            }
        }

        return ret;
    }

    int height(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            for(node->child.move(0);!node->child.end();node->child.next())
            {
                int h = height(node->child.current());
                ret = ret > h ? ret : h;
            }
            ret += 1;
        }

        return ret;
    }

    int degree(GTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = node->child.length();
            for(node->child.move(0);!node->child.end();node->child.next())
            {
                int d = degree(node->child.current());
                ret = ret > d ? ret : d;
            }
        }

        return ret;
    }
public:

    GTree()
    {

    }

    bool insert(TreeNode<T>* node)
    {
        bool ret = true;

        if(node != NULL)
        {
            if(this->m_root == NULL)
            {
                this->m_root = node;
            }
            else
            {
                GTreeNode<T>* np =  find(node->parent);
                if(np != NULL)
                {
                    GTreeNode<T>* n = dynamic_cast<GTreeNode<T>*>(node);
                    if(np->child.find(n) < 0)
                    {
                        np->child.insert(n);
                    }
                    else
                    {
                        ret = false;
                    }
                }
                else
                {
                    ret = false;
                }
            }
        }
        else
        {
            ret = false;
        }

        return ret;
    }

    bool insert(const T& value,TreeNode<T>* parent)
    {
        bool ret = true;

        GTreeNode<T>* node = GTreeNode<T>::NewNode();

        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;
            ret = insert(node);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to create new GTreeNode ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T& value)
    {
        GTree<T>* ret = NULL;

        GTreeNode<T>* node = find(value);
        if(node != NULL)
        {
            remove(node,ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The Parameter value is invalid ...");
        }
        return ret;
    }

    SharedPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        GTree<T>* ret = NULL;

        node = find(node);
        if(node != NULL)
        {
            remove(dynamic_cast<GTreeNode<T>*>(node),ret);
            m_queue.clear();
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"The Parameter value is invalid ...");
        }
        return ret;
    }

    GTreeNode<T>* find(const T& value)
    {
        return find(root(),value);
    }

    GTreeNode<T>* find(TreeNode<T>* node)
    {
        return find(root(),dynamic_cast<GTreeNode<T>*>(node));
    }

    GTreeNode<T>* root() const
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }

    int degree() const
    {
        return degree(root());
    }

    int count() const
    {
        return count(root());
    }

    int height() const
    {
        return height(root());
    }

    void clear()
    {
        clear(root());
        this->m_root = NULL;
        m_queue.clear();
    }

    bool begin()
    {
        bool ret = (root() != NULL);

        if(ret)
        {
            m_queue.clear();
            m_queue.add(root());
        }
        return ret;
    }

    bool end()
    {
        return (m_queue.length() == 0);
    }

    bool next()
    {
        bool ret = !end();

        if(ret)
        {
            GTreeNode<T>* node = m_queue.front();
            m_queue.remove();
            for(node->child.move(0);!node->child.end();node->child.next())
            {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }

    T current()
    {
        bool ret = !end();
        if(ret)
        {
            return m_queue.front()->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Can not get the element at the GTree ...");
        }
    }

    ~GTree()
    {
        clear();
    }

};

}
