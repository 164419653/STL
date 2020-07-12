#include"Object.h"
#include<cstdlib>
using namespace std;

namespace JYLib
{
	void* Object::operator new(size_t size) throw()
	{
		return malloc(size);
	}
	void Object::operator delete(void *p)
	{
		free(p);
	}

	void* Object::operator new[](size_t size) throw()
	{
		return malloc(size);
	}

	void Object::operator delete[](void *p)
	{
		free(p);
	}


	bool Object::operator ==(const Object& e) const
	{
		return (this == &e);
	}
	bool Object::operator !=(const Object& e) const
	{
		return (this != &e);
	}

    Object::~Object()
	{

	}
}
