#pragma once

#include"Graph.h"
#include"Exception.h"
#include"DynamicArray.h"

#include<iostream>
using namespace std;

namespace JYLib
{

template <int N,typename V,typename E>
class MatrixGraph : public Graph<V,E>
{
protected:
    V* m_vertexes[N];
    E* m_edges[N][N];
    int m_eCount;

public:
    MatrixGraph()
    {
        for(int i=0;i<N;i++)
        {
            m_vertexes[i] = NULL;
            for(int j=0;j<N;j++)
            {
                m_edges[i][j] = NULL;
            }
        }
        m_eCount = 0;
    }

    V getVertex(int i)
    {
        V ret;

        if(!getVertex(i,ret))
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i is invalid ...");
        }

        return ret;
    }

    bool getVertex(int i,V& value)
    {
        bool ret = (i >= 0) && (i < N);

        if(ret)
        {
            if(m_vertexes[i] != NULL)
            {
                value = *m_vertexes[i];
            }
            else
            {
                THROW_EXCEPTION(InvalidParamterException,"No value assign at this vertex ...");
            }
        }
        return ret;
    }

    bool setVertex(int i,const V& value)
    {
        bool ret = (i >= 0) && (i < N);

        if(ret)
        {
            V* data = m_vertexes[i];
            if(data == NULL)
            {
                data = new V();
            }
            if(data != NULL)
            {
                *data = value;

                m_vertexes[i] = data;
            }
            else
            {
               THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to create new Vertex ...");
            }
        }

        return ret;
    }

    SharedPointer<Array<int>> getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if((i>=0)&&(i<N))
        {
            int n = OD(i);
            ret = new DynamicArray<int>(n);
            if(ret != NULL)
            {
                for(int j=0,k=0;j<N;j++)
                {
                    if(m_edges[i][j] != NULL)
                    {
                        ret->set(k++,j);
                    }
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new array ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i is invalid ...");
        }

        return ret;
    }
    virtual E getEdge(int i,int j)
    {
        E ret;

        if(!getEdge(i,j,ret))
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i is invalid ...");
        }

        return ret;
    }

    virtual E getEdge(int i,int j,E& value)
    {
        bool ret = (i >= 0) && (i < N) && (j>=0) && (j<N);

        if(ret)
        {
            if(m_edges[i][j] != NULL)
            {
                value = *m_edges[i][j];
            }
            else
            {
                THROW_EXCEPTION(InvalidParamterException,"No value assign at this edge ...");
            }
        }
        return ret;
    }

    virtual bool setEdge(int i,int j,const E& value)
    {
        bool ret = (i >= 0) && (i < N) && (j>=0) && (j<N);

        if(ret)
        {
            E* e = m_edges[i][j];
            if(e == NULL)
            {
                e = new E();
                if(e != NULL)
                {
                    *e = value;
                    m_edges[i][j] = e;
                    m_eCount++;
                }
                else
                {
                    THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new edge ...");
                }
            }
            else
            {
                *e = value;
            }
        }

        return ret;
    }

    bool removeEdge(int i,int j)
    {
        bool ret = (i >= 0) && (i < N) && (j>=0) && (j<N);

        if(ret)
        {
            E* toDel = m_edges[i][j];
            m_edges[i][j] = NULL;
            if(toDel != NULL)
            {
                m_eCount--;

                delete toDel;
            }
        }

        return ret;
    }

    int vCount()
    {
        return  N;
    }

    int eCount()
    {
        return m_eCount;
    }

    int OD(int i)
    {
        int ret = 0;

        if((i>=0)&&(i<N))
        {
            for(int j=0;j<N;j++)
            {
                if(m_edges[i][j] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i is invalid ...");
        }
        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if((i>=0)&&(i<N))
        {
            for(int j=0;j<N;j++)
            {
                if(m_edges[j][i] != NULL)
                {
                    ret++;
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i is invalid ...");
        }
        return ret;
    }


    ~MatrixGraph()
    {
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                delete m_edges[i][j];
            }
            delete m_vertexes[i];
        }
    }
};

}
