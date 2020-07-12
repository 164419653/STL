#pragma once

#include"Tree.h"
#include"BTreeNode.h"
#include"Exception.h"
#include"LinkQueue.h"
#include"DynamicArray.h"

namespace JYLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T>*> m_queue;
    virtual BTreeNode<T>* find(BTreeNode<T>* node,const T& value) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            if(node->value == value)
            {
                ret = node;
            }
            else
            {
                ret = find(node->left,value);
                if(ret == NULL)
                {
                    ret = find(node->right,value);
                }
            }
        }

        return ret;
    }

    virtual BTreeNode<T>* find(BTreeNode<T>* node,BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret = NULL;

        if(node == obj)
        {
            ret = node;
        }
        else
        {
            if(node != NULL)
            {
                ret = find(node->left,obj);
                if(ret == NULL)
                {
                    ret = find(node->right,obj);
                }
            }
        }

        return ret;
    }

    virtual bool insert(BTreeNode<T>* n,BTreeNode<T>* np,BTreeNodePos pos)
    {
        bool ret = true;

        if(pos == ANY)
        {
            if(np->left == NULL)
            {
                np->left = n;
            }
            else if(np->right == NULL)
            {
                np->right = n;
            }
            else
            {
                ret = false;
            }
        }
        else if(pos == LEFT)
        {
           if(np->left == NULL)
           {
               np->left = n;
           }
           else
           {
               ret = false;
           }
        }
        else if(pos == RIGHT)
        {
            if(np->right == NULL)
            {
                np->right = n;
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

        return ret;
    }


    virtual void remove(BTreeNode<T>* node,BTree<T>*& ret)
    {
        ret = new BTree<T>();
        if(ret == NULL)
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new Tree ...");
        }
        else
        {
            if(root() == node)
            {
                this->m_root = NULL;
            }
            else
            {
                BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
                if(parent->left == node)
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
                node->parent = NULL;
            }
            ret->m_root = node;
            m_queue.clear();
        }
    }

    virtual void clear(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            clear(node->left);
            clear(node->right);

            if(node->flag())
            {
                delete node;
            }
        }
    }

    int count(BTreeNode<T>* node) const
    {
        return (node != NULL) ? count(node->left) + count(node->right)+1 : 0;
    }

    int height(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            int lh = height(node->left);
            int rh = height(node->right);

            ret = lh > rh ? lh+1 : rh+1;
        }

        return ret;
    }

    int degree(BTreeNode<T>* node) const
    {
        int ret = 0;

        if(node != NULL)
        {
            ret = !!(node->left) + !!(node->right);
            if(ret == 1 )
            {
                int ld = degree(node->left);
                ret = ret > ld ? ret : ld;
            }
            if(ret == 1)
            {
                int rd = degree(node->right);
                ret = ret > rd ? ret : rd;
            }
        }
        return ret;
    }

    void preOrder(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*> &queue)
    {
        if(node != NULL)
        {
            queue.add(node);
            preOrder(node->left,queue);
            preOrder(node->right,queue);
        }
    }

    void inOrder(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*> &queue)
    {
        if(node != NULL)
        {
            inOrder(node->left,queue);
            queue.add(node);
            inOrder(node->right,queue);
        }
    }

    void postOrder(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*> &queue)
    {
        if(node != NULL)
        {
            postOrder(node->left,queue);
            postOrder(node->right,queue);
            queue.add(node);
        }
    }

    BTreeNode<T>* clone(BTreeNode<T>* node) const
    {
        BTreeNode<T>* ret = NULL;

        if(node != NULL)
        {
            ret = BTreeNode<T>::NewNode();
            if(ret != NULL)
            {
                ret->value = node->value;
                ret->left = clone(node->left);
                ret->right = clone(node->right);

                if(ret->left != NULL)
                {
                    ret->left->parent = ret;
                }
                if(ret->right != NULL)
                {
                    ret->right->parent = ret;
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new node ...");
            }
        }

        return ret;
    }

    bool equal(BTreeNode<T>* lh,BTreeNode<T>* rh) const
    {
        if(lh == rh)
        {
            return true;
        }
        else if((lh != NULL) && (rh != NULL))
        {
            return (lh->value==rh->value) && equal(lh->left,rh->left) && equal(lh->right,rh->right);
        }
        else
        {
            return false;
        }
    }

    BTreeNode<T>* add(BTreeNode<T>* lh,BTreeNode<T>* rh) const
    {
        BTreeNode<T>* ret = NULL;

        if((lh != NULL) && (rh == NULL))
        {
            ret = clone(lh);
        }
        else if((lh == NULL) && (rh != NULL))
        {
            ret = clone(rh);
        }
        else if((lh != NULL) && (rh != NULL))
        {
            ret = BTreeNode<T>::NewNode();
            if(ret != NULL)
            {
                ret->value = lh->value + rh->value;
                ret->left = add(lh->left,rh->left);
                ret->right = add(lh->right,rh->right);

                if(ret->left != NULL)
                {
                    ret->left->parent = ret;
                }
                if(ret->right != NULL)
                {
                    ret->right->parent = ret;
                }

            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new node ...");
            }
        }

        return ret;
    }

public:

    bool insert(TreeNode<T>* node)
    {
        return insert(node,ANY);
    }

    virtual bool insert(TreeNode<T>* node,BTreeNodePos pos)
    {
        bool ret = true;
        if( node != NULL)
        {
            if(this->m_root == NULL)
            {
                node->parent = NULL;
                this->m_root = node;
            }
            else
            {
                BTreeNode<T>* np = find(node->parent);
                if(node != NULL)
                {
                    insert(dynamic_cast<BTreeNode<T>*>(node),np,pos);
                }
                else
                {
                    THROW_EXCEPTION(InvalidParamterException,"Invalid node parent ...");
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Invalid Parameter node  ...");
        }

        return ret;
    }

    bool insert(const T& value,TreeNode<T>* parent)
    {
        return insert(value,parent,ANY);
    }

    virtual bool insert(const T& value,TreeNode<T>* parent,BTreeNodePos pos)
    {
        bool ret = true;

        BTreeNode<T>* node = BTreeNode<T>::NewNode();

        if(node != NULL)
        {
            node->value = value;
            node->parent = parent;
            ret = insert(node,pos);
            if( !ret )
            {
                delete node;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to create new node ...");
        }

        return ret;
    }

    SharedPointer<Tree<T>> remove(const T& value)
    {
        BTree<T>* ret = NULL;

        BTreeNode<T>* node = find(value);
        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter node is invalid ...");
        }
        else
        {
            remove(node,ret);
        }
        return ret;
    }

    SharedPointer<Tree<T>> remove(TreeNode<T>* node)
    {
        BTree<T>* ret = NULL;

        node = find(node);
        if(node == NULL)
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter node is invalid ...");
        }
        else
        {
            remove(dynamic_cast<BTreeNode<T>*>(node),ret);
        }
        return ret;
    }

    BTreeNode<T>* find(const T& value)
    {
        return find(root(),value);
    }

    BTreeNode<T>* find(TreeNode<T>* node)
    {
        return find(root(),dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return dynamic_cast<BTreeNode<T>*>(this->m_root);
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
            BTreeNode<T>* node = m_queue.front();
            m_queue.remove();
            if(node->left) m_queue.add(node->left);
            if(node->right) m_queue.add(node->right);
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

    SharedPointer<Array<T>> traversal(BTTraversal order)
    {
        DynamicArray<T>* ret = NULL;
        LinkQueue<BTreeNode<T>*> queue;

        switch(order)
        {
        case PreOrder :
            preOrder(root(),queue);
            break;
        case InOrder :
            inOrder(root(),queue);
            break;
        case PostOrder :
            postOrder(root(),queue);
            break;
        default:
            THROW_EXCEPTION(InvalidParamterException,"Parameter order is invalid ...");
            break;
        }

        int len = queue.length();
        ret = new DynamicArray<T>(len);
        for(int i=0;i<len;i++)
        {
            ret->set(i,queue.front()->value);
            queue.remove();
        }
        return ret;
    }

    SharedPointer<BTree<T>> clone() const
    {
        BTree<T>* ret = new BTree<T>();
        if(ret != NULL)
        {
            ret->m_root = clone(root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new tree ...");
        }
        return ret;
    }

    bool operator==(BTree<T>& obj)
    {
        return equal(root(),obj.root());
    }

    bool operator!=(BTree<T>& obj)
    {
        return !(*this == obj);
    }

    SharedPointer<BTree<T>> add(BTree<T>& obj)
    {
        BTree<T>* ret = new BTree<T>();
        if(ret != NULL)
        {
            ret->m_root = add(root(),obj.root());
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new tree ...");
        }
        return ret;
    }

    ~BTree()
    {
        clear();
    }
};

}
