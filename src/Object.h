#pragma once

#include<cstdlib>

namespace JYLib
{
	class Object
	{
	public:
        void* operator new(unsigned int  size) throw();
		void operator delete(void *p);

        void* operator new[](unsigned int size) throw();
		void operator delete[](void *p);

		bool operator ==(const Object& e) const;
		bool operator !=(const Object& e) const;

		virtual ~Object() = 0;
	};
}
