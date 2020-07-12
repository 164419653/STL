#pragma once

#include<cstring>
#include<cstdlib>

#include "Object.h"

namespace JYLib
{
	#define THROW_EXCEPTION(e,m) throw e(m,__FILE__,__LINE__)

	class Exception : public Object
	{
	protected:
		char *m_message;
		char *m_location;

		void init(const char *message, const char *file, int line);

	public:
		Exception(const char *message);
		Exception(const char* file, int line);
		Exception(const char *message, const char *file, int line);

		Exception(const Exception &obj);

		Exception& operator=(const Exception& obj);

		virtual ~Exception();

		virtual const char* message() const;
		virtual const char* location() const;

	};


	class ArithmeticException :public Exception
	{
	public:
		ArithmeticException() :Exception(NULL, NULL, 0) {}
		ArithmeticException(const char *message) :Exception(message) {}
		ArithmeticException(const char *file,int line):Exception(file,line){}
		ArithmeticException(const char* message,const char* file,int line):Exception(message,file,line){}

		ArithmeticException(const ArithmeticException&obj):Exception(obj){}
		ArithmeticException& operator=(const ArithmeticException &obj)
		{
            Exception::operator=(obj);
			return *this;
		}
	};

	class NullPointerException :public Exception
	{
	public:
		NullPointerException() :Exception(NULL, NULL, 0) {}
		NullPointerException(const char *message) :Exception(message) {}
		NullPointerException(const char *file, int line) :Exception(file, line) {}
		NullPointerException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		NullPointerException(const ArithmeticException&obj) :Exception(obj) {}
		NullPointerException& operator=(const ArithmeticException &obj)
		{
            Exception::operator=(obj);
			return *this;
		}
	};

	class IndexOutOfBoundsException :public Exception
	{
	public:
		IndexOutOfBoundsException() :Exception(NULL, NULL, 0) {}
		IndexOutOfBoundsException(const char *message) :Exception(message) {}
		IndexOutOfBoundsException(const char *file, int line) :Exception(file, line) {}
		IndexOutOfBoundsException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		IndexOutOfBoundsException(const ArithmeticException&obj) :Exception(obj) {}
		IndexOutOfBoundsException& operator=(const ArithmeticException &obj)
		{
            Exception::operator=(obj);
			return *this;
		}
	};

	class NoEnoughMemoryException :public Exception
	{
	public:
		NoEnoughMemoryException() :Exception(NULL, NULL, 0) {}
		NoEnoughMemoryException(const char *message) :Exception(message) {}
		NoEnoughMemoryException(const char *file, int line) :Exception(file, line) {}
		NoEnoughMemoryException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		NoEnoughMemoryException(const ArithmeticException&obj) :Exception(obj) {}
		NoEnoughMemoryException& operator=(const ArithmeticException &obj)
		{
            Exception::operator=(obj);
			return *this;
		}
	};

	class InvalidParamterException :public Exception
	{
	public:
		InvalidParamterException() :Exception(NULL, NULL, 0) {}
		InvalidParamterException(const char *message) :Exception(message) {}
		InvalidParamterException(const char *file, int line) :Exception(file, line) {}
		InvalidParamterException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		InvalidParamterException(const ArithmeticException&obj) :Exception(obj) {}
		InvalidParamterException& operator=(const ArithmeticException &obj)
		{
            Exception::operator=(obj);
			return *this;
		}
	};

	class InvalidOperationException :public Exception
	{
	public:
		InvalidOperationException() :Exception(NULL, NULL, 0) {}
		InvalidOperationException(const char *message) :Exception(message) {}
		InvalidOperationException(const char *file, int line) :Exception(file, line) {}
		InvalidOperationException(const char* message, const char* file, int line) :Exception(message, file, line) {}

		InvalidOperationException(const ArithmeticException&obj) :Exception(obj) {}
		InvalidOperationException& operator=(const ArithmeticException &obj)
		{
            Exception::operator=(obj);
			return *this;
		}
	};
}
