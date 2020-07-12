#pragma once

#include"TreeNode.h"

namespace JYLib
{

enum BTreeNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    static BTreeNode<T>* NewNode()
    {

        BTreeNode<T>* ret = new BTreeNode();
        if(ret != NULL)
        {
            ret->m_flag = true;
        }
        return ret;
    }
};

}
