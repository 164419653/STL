#pragma once

namespace JYLib
{

    class Object
    {
    public:
        void* operator new (unsigned int size) throw();
        void operator delete (void* p);
        void* operator new[](unsigned int size) throw();
        void operator delete[](void* p);
        bool operator == (const Object& obj);
        bool operator != (const Object& obj);
        virtual ~Object() = 0;
    };
}