#pragma once

#include"Object.h"

namespace JYLib
{

class String : public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);
    bool equal(const char* s1,const char* s2,int len) const;
    static int* make_pmt(const char* s);
    static int kmp(const char* s,const char* p);
public:
    String();
    String(const char c);
    String(const char* s);
    String(const String& s);

    int length() const;
    const char* str() const;
    bool startWith(const char* s) const;
    bool startWith(String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;
    String& insert(int i,const char* s);
    String& insert(int i,const String& s);
    String& trim();
    int indexOf(const char* s) const;
    int indexOf(const String& s) const;
    String&  remove(int index,int len);
    String& remove(const char* s);
    String& remove(const String& s);
    String& replace(const char* s,const char* t);
    String& replace(const String& s,const char* t);
    String& replace(const char* s,const String& t);
    String& replace(const String& s,const String& t);
    String sub(int i,int len) const;

    bool operator==(const char* s) const;
    bool operator==(const String& s) const;
    bool operator!=(const char* s) const;
    bool operator!=(const String& s) const;
    bool operator>(const char* s) const;
    bool operator>(const String& s) const;
    bool operator<(const char* s) const;
    bool operator<(const String& s) const;
    bool operator>=(const char* s) const;
    bool operator>=(const String& s) const;
    bool operator<=(const char* s) const;
    bool operator<=(const String& s) const;



    String operator+(const char* s);
    String operator+(const String& s);
    String& operator+=(const char* s);
    String& operator+=(const String& s);
    String operator-(const char* s);
    String operator-(const String& s);
    String& operator-=(const char* s);
    String& operator-=(const String& s);

    String& operator=(const char c);
    String& operator=(const char* s);
    String& operator=(const String& s);
    char& operator[](int i);
    char operator[](int i) const;

};
}
