
#include<cstdlib>
#include<cstring>
#include"JYString.h"
#include"Exception.h"

namespace JYLib
{

void String::init(const char* s)
{
    m_str = strdup(s);

    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory to use in String ...");
    }
}

bool String::equal(const char* s1,const char* s2,int len) const
{
    bool ret = true;
    for(int i=0;i<len && ret;i++)
    {
        ret = (s1[i]==s2[i]);
    }
    return ret;
}


int* String::make_pmt(const char* s)
{
    int* ret = NULL;
    if(s!=NULL && strlen(s)>0)
    {
        ret = static_cast<int*>(malloc(strlen(s)));
        if(ret)
        {
            int ll = 0;
            ret[0] = 0;
            int len = strlen(s);
            for(int i=1;i<len;i++)
            {
                while((ll>0) && (s[i]!=s[ll]))
                {
                    ll = ret[ll-1];
                }

                if(s[i] == s[ll])
                {
                    ll++;
                }
                ret[i] = ll;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory at make_pmt ...");
        }
    }
    return ret;
}


int String::kmp(const char* s,const char* p)
{
    int ret = -1;
    if(s == NULL) return ret;
    if(p == NULL) return ret;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);
    if(pmt && sl>=pl)
    {
        for(int i=0,j=0;i<sl;i++)
        {

            while((j>0)&&(s[i]!=p[j]))
            {
                j = pmt[j-1];
            }
            if(s[i] == p[j])
            {
                j++;
            }
            if(j == pl)
            {
                ret = i+1-pl;
                break;
            }
        }
    }
    return ret;
}

String::String()
{
    init("");
}

String::String(const char c)
{
    char s[] = {c,'\0'};
    init(s);
}

String::String(const char* s)
{
    init(s ? s : "");
}

String::String(const String& s)
{
    init(s.m_str);
}

int String::length() const
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::startWith(const char* s) const
{
    if(s == NULL) return false;
    int len = strlen(s);
    if(len > m_length) return false;
    return equal(m_str,s,len);
}

bool String::startWith(String& s) const
{
    return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    if(s == NULL) return false;
    int len = strlen(s);
    if(len > m_length) return false;
    const char* str = m_str + (m_length - len);
    return equal(str,s,len);
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i,const char* s)
{
    if((i>=0) && (i<=m_length))
    {
        if(s!=NULL && s[0]!='\0')
        {
            int len = strlen(s);
            char* str = static_cast<char*>(malloc(len+m_length+1));
            if(str)
            {
                strncpy(str,m_str,i);
                strncpy(str+i,s,len);
                strncpy(str+i+len,m_str+i,m_length-i);

                str[len + m_length] = '\0';
                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory at String::insert ...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"The parameter i is not invalid...");
    }

    return *this;
}

String& String::insert(int i,const String& s)
{
    return insert(i,s.m_str);
}

String& String::trim()
{
    int b = 0;
    int e = m_length - 1;
    while(m_str[b] == ' ') b++;
    while(m_str[e] == ' ' && e>=0) e--;
    int len = e - b + 1;

    if(len < 0)
    {
        char *str = strdup("");
        if(str)
        {
            free(m_str);
            m_str = str;
            m_length = 0;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory at String::trim ...");
        }

    }
    else if(len < m_length)
    {
        char* str = static_cast<char*>(malloc(len+1));
        if(str)
        {
            strncpy(str,m_str+b,len);
            free(m_str);
            m_str = str;
            str[len+1] = '\0';
            m_length = len;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"no enough memory at String::trim ...");
        }
    }
    return *this;
}

int String::indexOf(const char* s) const
{
    return kmp(m_str,s);
}

int String::indexOf(const String& s) const
{
    return kmp(m_str,s.m_str);
}

String&  String::remove(int index,int len)
{
    if((index >= 0)&&(index <= m_length))
    {
        if(index+len <= m_length)
        {
            int nl = m_length - len;
            char* str = static_cast<char*>(malloc(nl+1));
            if(str)
            {
                strncpy(str,m_str,index);
                strncpy(str+index,m_str+len+index,m_length-len-index);
                str[nl] = '\0';

                free(m_str);
                m_str = str;
                m_length = nl;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No memory at String::remove ...");
            }
        }
    }
    return *this;
}

String& String::remove(const char* s)
{
    return remove(indexOf(s),s?strlen(s):0);
}

String& String::remove(const String& s)
{
    return remove(indexOf(s.m_str),s.m_length);
}


String& String::replace(const char* s,const char* t)
{
    int index = indexOf(s);
    if(index >= 0)
    {
        remove(s);
        insert(index,t);
    }
    return *this;
}

String& String::replace(const String& s,const char* t)
{
    return replace(s.m_str,t);
}

String& String::replace(const char* s,const String& t)
{
    return replace(s,t.m_str);
}

String& String::replace(const String& s,const String& t)
{
    return replace(s.m_str,t.m_str);
}

String String::sub(int i,int len) const
{
    String ret;
    if((i >= 0)&&(i< m_length))
    {
        if(len < 0) len = 0;
        if((len+i) > m_length) len = m_length - i;
        char* str = static_cast<char*>(malloc(len+1));
        strncpy(str,m_str+i,len);
        str[len] = '\0';

        ret = str;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is not invalid ...");
    }
    return ret;
}

bool String::operator==(const char* s) const
{
    return (strcmp(m_str,s ? s : "") == 0);
}

bool String::operator==(const String& s) const
{
    return (strcmp(m_str,s.m_str) == 0);
}

bool String::operator!=(const char* s) const
{
    return (strcmp(m_str,s ? s : "") != 0);
}

bool String::operator!=(const String& s) const
{
    return (strcmp(m_str,s.m_str) != 0);
}

bool String::operator>(const char* s) const
{
    return (strcmp(m_str,s ? s : "") > 0);
}

bool String::operator>(const String& s) const
{
    return (strcmp(m_str,s.m_str) > 0);
}

bool String::operator<(const char* s) const
{
    return (strcmp(m_str,s ? s : "") < 0);
}

bool String::operator<(const String& s) const
{
    return (strcmp(m_str,s.m_str) < 0);
}

bool String::operator>=(const char* s) const
{
    return (strcmp(m_str,s ? s : "") >= 0);
}

bool String::operator>=(const String& s) const
{
    return (strcmp(m_str,s.m_str) >= 0);
}

bool String::operator<=(const char* s) const
{
    return (strcmp(m_str,s ? s : "") <= 0);
}

bool String::operator<=(const String& s) const
{
    return (strcmp(m_str,s.m_str) <= 0);
}

String String::operator+(const char* s)
{
    String ret;

    int len = m_length + strlen(s ? s : "");
    char* str = static_cast<char*>(malloc(len+1));

    if(str)
    {
        strcpy(str,m_str);
        strcat(str,s ? s : "");

        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory for String at operation [String::operator+] ...");
    }

    return ret;
}

String String::operator+(const String& s)
{
    return (*this + s.m_str);
}


String& String::operator+=(const char* s)
{
    return (*this = *this + s);
}

String& String::operator+=(const String& s)
{
    return (*this = *this + s.m_str);
}


String String::operator-(const char* s)
{
    return String(*this).remove(s);
}

String String::operator-(const String& s)
{
    return String(*this).remove(s);
}

String& String::operator-=(const char* s)
{
    return remove(s);
}

String& String::operator-=(const String& s)
{
    return remove(s);
}

String& String::operator=(const char c)
{
    char s[] = {c,'\0'};
    *this = s;
    return *this;
}

String& String::operator=(const char* s)
{
    if(m_str != s)
    {
        char* str = strdup(s ? s : "");
        if(str)
        {
            free(m_str);
            m_str = str;
            m_length = strlen(s);
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory for String at operation [String::operator+] ...");
        }
    }

    return *this;
}

String& String::operator=(const String& s)
{
    *this = s.m_str;
    return *this;
}

char& String::operator[](int i)
{
    if((i>=0)&&(i<m_length))
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Parameter i is not invalid...");
    }
}

char String::operator[](int i) const
{
    return (const_cast<String&>((*this)))[i];  // const_cast just for references or pointer
}



}
