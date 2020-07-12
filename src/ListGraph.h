#pragma once

#include"Graph.h"
#include"LinkList.h"
#include"Exception.h"
#include"DynamicArray.h"

namespace JYLib
{

template <typename V,typename E>
class ListGraph : public Graph<V,E>
{
protected:
    struct Vertex : public Object
    {
        V* data;
        LinkList<Edge<E>> edge;

        Vertex()
        {
            data = NULL;
        }
    };

    LinkList<Vertex *> m_list;
public:

    ListGraph()
    {

    }
    ListGraph(unsigned int n)
    {
        for(unsigned int i = 0;i<n;i++)
        {
            addVertex();
        }
    }

    int addVertex()
    {
        int ret = -1;
        Vertex* v = new Vertex();
        if(v != NULL)
        {
            m_list.insert(v);
            ret = m_list.length()-1;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enouth memory to create new Vertex Object ...");
        }

        return ret;
    }

    int addVertex(const V& value)
    {
        int ret = -1;

        ret = addVertex();
        if(ret >= 0)
        {
            setVertex(ret,value);
        }

        return ret;
    }

    bool setVertex(int i,const V& value)
    {
        bool ret = (i>=0) && (i<m_list.length());

        if(ret)
        {
            Vertex* v = m_list.get(i);
            V* data = v->data;
            if(data == NULL)
            {
                data = new V();
            }
            if(data != NULL)
            {
                *data = value;
                v->data = data;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memory to create new v ...");
            }

        }
        return ret;
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

    bool getVertex(int i, V& value)
    {
        bool ret = (i>=0) && (i<m_list.length());

        if(ret)
        {
            Vertex* v = m_list.get(i);
            if(v->data != NULL)
            {
                value = *(v->data);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"No value at this vertex ...");
            }
        }

        return ret;
    }

    void removeVertex()
    {
        if(m_list.length() > 0)
        {
            int index = m_list.length()-1;
            Vertex* v = m_list.get(index);
            if(m_list.remove(index))
            {
                for(int i = (m_list.move(0),0);!m_list.end();m_list.next(),i++)
                {
                    int pos = m_list.current()->edge.find(Edge<E>(i,index));
                    if(pos >= 0)
                    {
                        m_list.current()->edge.remove(pos);
                    }
                }
                delete v->data;
                delete v;
            }

        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException,"Exception at removeVertex ...");
        }
    }

    SharedPointer<Array<int>> getAdjacent(int i)
    {
        DynamicArray<int>* ret = NULL;

        if((i>=0) && (i<m_list.length()))
        {
            Vertex* v = m_list.get(i);
            ret = new DynamicArray<int>(v->edge.length());
            if(ret != NULL)
            {
                for(int k=(v->edge.move(0),0);!v->edge.end();k++,v->edge.next())
                {
                    ret->set(k,v->edge.current().e);
                }
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No enough to create new array ...");
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i is invalid ...");
        }
        return ret;
    }

    E getEdge(int i,int j)
    {
        E ret;

        if(!getEdge(i,j,ret))
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter i or j is invalid ...");
        }

        return ret;
    }

    bool getEdge(int i,int j,E& value)
    {
        bool ret = (i>=0) && (j>=0) && (i<m_list.length()) && (j<m_list.length());

        if(ret)
        {
            Vertex* v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i,j));
            if(pos >= 0)
            {
                value = v->edge.get(pos).data;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException,"Exception at getEdge(int i,int j,E& value)");
            }
        }

        return ret;
    }

    bool setEdge(int i,int j,const E& value)
    {
        bool ret = (i>=0) && (j>=0) && (i<m_list.length()) && (j<m_list.length());

        if(ret)
        {
            Vertex* v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i,j));
            if(pos >= 0)
            {
                ret = v->edge.set(pos,Edge<E>(i,j,value));
            }
            else
            {
                ret = v->edge.insert(0,Edge<E>(i,j,value));
            }
        }

        return ret;
    }

    bool removeEdge(int i,int j)
    {
        bool ret = (i>=0) && (j>=0) && (i<m_list.length()) && (j<m_list.length());

        if(ret)
        {
            Vertex* v = m_list.get(i);
            int pos = v->edge.find(Edge<E>(i,j));
            if(pos >= 0)
            {
                ret = v->edge.remove(pos);
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter is invalid ...");
        }

        return ret;
    }

    int vCount()
    {
        return m_list.length();
    }

    int eCount()
    {
        int ret = 0;
        for(m_list.move(0);!m_list.end();m_list.next())
        {
            ret+=m_list.current()->edge.length();
        }
        return ret;
    }

    int ID(int i)
    {
        int ret = 0;

        if((i >= 0) && ( i< m_list.length()))
        {
            for(m_list.move(0);!m_list.end();m_list.next())
            {
                LinkList<Edge<E>>& edges = m_list.current()->edge;
                for(edges.move(0);!edges.end();edges.next())
                {
                    if(edges.current().e == i)
                    {
                        ret++;
                        break;
                    }
                }
            }
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter is invalid ...");
        }

        return ret;
    }

    int OD(int i)
    {
        int ret = 0;

        if((i >= 0) && ( i< m_list.length()))
        {
            ret = m_list.get(i)->edge.length();
        }
        else
        {
            THROW_EXCEPTION(InvalidParamterException,"Parameter is invalid ...");
        }

        return ret;
    }



    ~ListGraph()
    {
        while(m_list.length()>0)
        {
            Vertex* v = m_list.get(0);
            m_list.remove(0);

            delete v->data;
            delete v;
        }
    }

};

}
