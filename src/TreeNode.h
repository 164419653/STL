#pragma once

#include"Object.h"

namespace JYLib
{

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;

    TreeNode(const TreeNode<T>&);
    TreeNode<T>& operator=(const TreeNode<T>&);

    void* operator new(unsigned int size)
    {
        return Object::operator new(size);
    }
public:
    T value;
    TreeNode* parent;
    TreeNode()
    {
        this->parent = NULL;
        m_flag = false;
    }

    bool flag()
    {
        return m_flag;
    }

    virtual ~TreeNode() = 0;
};

template <typename T>
TreeNode<T>::~TreeNode()
{

}

}
