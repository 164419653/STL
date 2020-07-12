#pragma once

#include"LinkList.h"
#include"TreeNode.h"

namespace JYLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList<GTreeNode<T>*> child;

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret = new GTreeNode();
        if(ret != NULL)
        {
            ret->m_flag = true;
        }
        return ret;
    }
};

}
