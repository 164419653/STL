#pragma once

#include "TreeNode.h"
#include "LinkList.h"

namespace JYLib
{

    template < typename T >
    class GTreeNode : public TreeNode<T>
    {
    public:
        LinkList<GTreeNode<T>*> child;

        static GTreeNode<T>* NewNode()
        {
            GTreeNode<T>* ret = new GTreeNode<T>();

            if (ret != NULL)
            {
                ret->m_flag = true;
            }

            return ret;
        }
    };


}
