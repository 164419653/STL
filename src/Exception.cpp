#include "Exception.h"

#include<cstring>
#include<cstdlib>
#include<string.h>

using namespace std;

namespace JYLib
{
	void Exception::init(const char *message, const char *file, int line)
	{
		m_message = (message ? strdup(message) :NULL);

		if (file != NULL)
		{
			char li[16];
			itoa(line, li, 10);
			m_location = static_cast<char*>(malloc(strlen(file) + strlen(li) + 2));

            if (m_location != NULL)
			{
				m_location = strcpy(m_location, file);
				m_location = strcat(m_location, ":");
				m_location = strcat(m_location, li);
			}
		}
		else
		{
			m_location = NULL;
		}
	}


	Exception::Exception(const char *message)
	{
		init(message, NULL, 0);
	}
	Exception::Exception(const char* file, int line)
	{
		init(NULL, file, line);
	}
	Exception::Exception(const char *message, const char *file, int line)
	{
		init(message, file, line);
	}


	Exception::Exception(const Exception &obj)
	{
		m_message = strdup(obj.m_message);
		m_location = strdup(obj.m_location);

	}

	Exception& Exception::operator=(const Exception& obj)
	{
		if (this != &obj)
		{
			free(m_message);
			free(m_location);

			m_message = strdup(obj.m_message);
			m_location = strdup(obj.m_location);
		}

		return *this;
	}


	const char* Exception::message() const
	{
		return m_message;
	}
	const char* Exception::location() const  // 注意点，在生命virtual函数时只需要在函数声明时注明就可以
	{
		return m_location;
	}

	Exception::~Exception()
	{
		free(m_message);
		free(m_location);
	}
}
