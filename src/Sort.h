#pragma once

#include"Object.h"
#include"cstdlib"
#include"Array.h"

namespace JYLib
{
class Sort : public Object
{
private:
    Sort();
    Sort(const Sort& obj);
    Sort& operator=(const Sort& obj);

    template<typename T>
    static void Swap(T& e1,T& e2)
    {
        T t(e1);
        e1 = e2;
        e2 = t;
    }

    template<typename T>
    static void Merge(T array[],T helper[],int begin,int mid,int end, bool min2max)
    {
        int i = begin;
        int j = mid + 1;
        int k = begin;
        while((i<=mid)&&(j<=end))
        {
            if(min2max?array[i] < array[j]:array[j]<array[i])
            {
                helper[k++] = array[i++];
            }
            else
            {
                helper[k++] = array[j++];
            }
        }
        while(i<=mid)
        {
            helper[k++] = array[i++];
        }
        while(j<=end)
        {
            helper[k++] = array[j++];
        }
        for(k=begin;k<=end;k++)
        {
            array[k] = helper[k];
        }
    }

    template<typename T>
    static void Merge(T array[],T helper[],int begin,int end, bool min2max)
    {
        if(begin < end)
        {
            int mid = (end + begin) / 2;
            Merge(array,helper,begin,mid,min2max);
            Merge(array,helper,mid+1,end,min2max);
            Merge(array,helper,begin,mid,end,min2max);
        }
    }

    template<typename T>
    static int Partition(T array[],int begin,int end,bool min2max)
    {
        int pv = array[begin];
        while (begin < end)
        {
            while((begin<end)&&(min2max?array[end]>pv:array[end]<pv))
            {
                end--;
            }
            Swap(array[end],array[begin]);
            while((begin<end)&&(min2max?array[begin]<=pv:array[begin]>=pv))
            {
                begin++;
            }
            Swap(array[begin],array[end]);
        }
        return begin;
   }

    template<typename T>
    static void Quick(T array[],int begin,int end,bool min2max)
    {
        if(begin < end)
        {
            int pivot = Partition(array,begin,end,min2max);
            Quick(array,begin,pivot-1,min2max);
            Quick(array,pivot+1,end,min2max);
        }
    }

public:
    template<typename T>
    static void Select(T array[],int len,bool min2max = true)
    {
        for(int i=0;i<len-1;i++)
        {
            int min = i;
            for(int j=i+1;j<len;j++)
            {
                if(min2max?array[j]<array[min]:array[j]>array[min])
                {
                    min = j;
                }
            }
            if(min != i)
            {
                Swap(array[min],array[i]);

            }
        }
    }

    template<typename T>
    static void Insert(T array[],int len,bool min2max = true)
    {
        for(int i=1;i<len;i++)
        {
            T e = array[i];
            int k = i;
            for(int j=i;j>0&&(min2max?e<array[j-1]:e>array[j-1]);j--)
            {
                array[j] = array[j-1];
                k = j-1;
            }
            if(i!=k)
            {
                array[k] = e;
            }
        }
    }

    template<typename T>
    static void Bubble(T array[],int len,bool min2max = true)
    {
        bool exchange = true;
        for(int i=0;(i<len-1)&&(exchange);i++)
        {
            exchange = false;
            for(int j=len-1;j>i;j--)
            {
                if(min2max?array[j]<array[j-1]:array[j]>array[j-1])
                {
                    Swap(array[j],array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    template<typename T>
    static void Shell(T array[],int len,bool min2max = true)
    {
        int d = len;
        do
        {
            d = d / 3 + 1;
            for(int i=d;i<len;i+=d)
            {
                T e = array[i];
                int k = i;
                for(int j=i;j>0&&(min2max?e<array[j-d]:e>array[j-d]);j-=d)
                {
                    array[j] = array[j-d];
                    k = j-d;
                }
                if(i!=k)
                {
                    array[k] = e;
                }
            }
        }while(d > 1);
    }

    template<typename T>
    static void Merge(T array[],int len, bool min2max = true)
    {
        T *helper = new T[len];
        if(helper != NULL)
        {
            Merge(array,helper,0,len-1,min2max);
        }

        delete[] helper;
    }

    template<typename T>
    static void Quick(T array[],int len,bool min2max=true)
    {
        Quick(array,0,len-1,min2max);
    }

    template<typename T>
    static void Select(Array<T>& array,bool min2max=true)
    {
        Select(array.array(),array.length(),min2max);
    }

    template<typename T>
    static void Insert(Array<T>& array,bool min2max=true)
    {
        Insert(array.array(),array.length(),min2max);
    }

    template<typename T>
    static void Bubble(Array<T>& array,bool min2max=true)
    {
        Bubble(array.array(),array.length(),min2max);
    }

    template<typename T>
    static void Shell(Array<T>& array,bool min2max=true)
    {
        Shell(array.array(),array.length(),min2max);
    }

    template<typename T>
    static void Merge(Array<T>& array,bool min2max=true)
    {
        Merge(array.array(),array.length(),min2max);
    }

    template<typename T>
    static void Quick(Array<T>& array,bool min2max=true)
    {
        Quick(array.array(),array.length(),min2max);
    }
};


}
