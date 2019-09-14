#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstring>
#include <cstdlib>
#include "String.h"
#include "expection.h"
using namespace std;
namespace DTLib{
void String::init(const char *s)
{
	m_str = _strdup(s);
	if( m_str )
	{
		m_length = strlen(m_str);
	}
	else
	{
		THROW_EXPECTION(NoenoughMemmoryExpection,"No enough memory to creat a m_str");
	}
}
bool String::equal(const char *l,const char *r,int len) const
{
	bool ret = true;
	for(int i=0;i<len;i++)
	{
		ret = ret && (l[i]==r[i]);
		
	}
	return ret;
}
bool String::startwith(const char *s) const
{
	bool ret = (s != NULL);
	if(ret)
	{
		int len = strlen(s);
		ret = (ret && (len < m_length) && equal(m_str,s,len));
	}
	return ret;
}
bool String::startwith(const String&s)const
{
	return startwith(s.m_str);
}
bool String::endof(const char *s) const
{
	bool ret = (s != NULL);
	if(ret)
	{
		int len = strlen(s);
		char *str = m_str + (m_length-len);   //begin at 0;
		ret = (ret && (len <m_length) && equal(str,s,len));
	}
	return ret;
}
bool String::endof(const String&s)const
{
	return endof(s.m_str);
}

int * String::make_pmt(const char *p)   //创造pmt表格 
{
	int len = strlen(p);
	int *ret = static_cast<int*>(malloc(sizeof(int) * len)); 
	if( ret !=NULL)
	{
		int ll = 0;
		ret[0] = 0;
		for(int i=1;i<len;i++)   //第0个确定是0 无需在比较 
		{
			while( (ll>0) && (p[ll]!=p[i]))  //不相等的情况下递推向前 
			{
				ll = ret[ll-1];
			}
			if(p[ll] == p[i])
			{
				ll++;
			}
			ret[i] = ll;
		}
		
	}
	return ret;
}
int String::kmp(const char *soc,const char *dest)   //dest为在soc中要查找的字符串 
{
	int ret = -1; 
	int sl = strlen(soc);
	int pl = strlen(dest);
	int *pmt = make_pmt(dest);
	
	if( (pmt!=NULL) && (pl>0)&& (pl<=sl))    //少写了一个等号。需要考虑两个字符串长度完全相等的情况 
	{
		for(int i=0,j = 0;i<sl;i++)
		{
			while((j>0) && (soc[i]!=dest[j]))
			{
				j= pmt[j-1]; 
			}
			if(soc[i] == dest[j])
			{
				j++;
			}
			if( j== pl )
			{
				ret = i-pl+1;
			}
		}
	}
	free(pmt);
	return ret;
}

String& String::insert( int i,const char *s)
{
	if((0<=i) && (i<=m_length))
	{
		if((s!=NULL) && (s[0]!='\0'))
		{
			int len = strlen(s);
			char *str = reinterpret_cast<char *>(malloc(m_length+len+1));//分配对空间，便于复制 
			if( str )
			{
				strncpy(str,m_str,i);
				strncpy(str + i,s,len);
				strncpy(str+i+len,m_str+i,m_length-i);
				
				str[m_length+len] = '\0';
				free(m_str);
				m_str = str;
				m_length = m_length+len;
				
			}
			else
			{
				THROW_EXPECTION(NoenoughMemmoryExpection,"No enough memory to creat a m_str");
			}
		}
	}
	return *this;
}
String& String::insert(int i,String&s)
{
	return insert(i,s.m_str);
}
String& String::trim()  //去掉字符串两端的空白字符 
{
	int b = 0;
	int e = m_length-1;
	
	while(m_str[b] == ' ') b++;
	while(m_str[e]== ' ') e--;
	
	if( b== 0)
	{
		m_str[e+1] = '\0';
		m_length = e +1;	
	} 
	else
	{
		for(int i=0,j = b;j<=e;i++,j++)
		{
			m_str[i] = m_str[j];
		}
		m_str[e-b+1] = '\0';
		m_length = e-b+1;	
	}
	return *this;
} 

int String::indexof(const char *s) const
{
	return kmp(m_str,s ? s : "");
}
int String::indexof(const String&s)const
{
	return kmp(m_str,s.m_str);
}

String& String::remove(int i,int len)
{
	if((0<=i) && (i<m_length))
	{
		int n = i;
		int m = i+len;
		while( (n<m) && (m<m_length))
		{
			m_str[n++] = m_str[m++];	
		}
		m_str[n] = '\0';
		m_length = n;
	}
	return *this;
}
String& String::remove(const char *s)
{
	
	return remove(indexof(s),s?strlen(s):0);
	
} 
String& String::remove(const String&s)
{
	return remove(indexof(s),s.m_length);
}

String& String::replace(const char *t,const char *s)   // t为被替换的字符串，s 为替代的字符串 
{
	int index = indexof(t);
	if(index > 0)
	{
		remove(t);
		insert(index,s);
	}
	return *this;
}
String& String::replace(const String&t,const char *s)
{
	return replace(t.m_str,s);
}
String& String::replace(const char *t, const String&s)
{
	return replace(t,s.m_str);
}
String& String::replace(const String&t, const String&s)
{
	return replace(t.m_str,s.m_str);
}

String String::sub(int i,int len)   // 从字符串中提取另一个字符串 
{
	String ret;
	if((0<=i) && (i< m_length))
	{
		if(len < 0) len = 0;
		if( len>m_length) len = m_length-i;
		char *str = reinterpret_cast<char *> (malloc(len+1));
		strncpy(str,m_str+i,len);
		ret = str;
	}
	return ret;
}

String::String()
{
	init("");
}
String::String( char c)
{
    const char s[] = {c,'\0'};
	init(s);
	
}
String::String( char *s)
{
	init(s ? s: " ") ;// S是空指针返回空字符串 
}
String::String ( const String &s)
{
	init(s.m_str) ;
}
int String::length() const
{
	return m_length;
}
 const char* String::str() const
 {
 	return m_str;
 }
String::~String()
{
	free(m_str);
}
bool String::operator == ( const String&s ) const
{
	return ( strcmp(m_str,s.m_str) == 0);
}
bool String::operator == ( const char *s) const
{
	return ( strcmp(m_str,s?s:"") == 0);
}
bool String::operator != ( const String&s ) const
{
	return !(*this == s);
}
bool String::operator != ( const char *s) const
{
	return !(*this == s);
}
bool String::operator >  ( const String&s ) const
{
	return ( strcmp(m_str,s.m_str) > 0);
}
bool String::operator >  ( const char *s) const
{
	return ( strcmp(m_str,s?s:"") > 0);
}
bool String::operator <  ( const String&s ) const
{
	return ( strcmp(m_str,s.m_str) < 0);
}
bool String::operator <  ( const char *s) const
{
	return ( strcmp(m_str,s?s:"") < 0);
}
bool String::operator >= ( const String&s ) const
{
	return ( strcmp(m_str,s.m_str) >= 0);
}
bool String::operator >= ( const char *s) const
{
	return ( strcmp(m_str,s?s:"") >= 0);
}
bool String::operator <= ( const String&s ) const
{
	return ( strcmp(m_str,s.m_str) <= 0);
}
bool String::operator <= ( const char *s) const
{
	return ( strcmp(m_str,s?s:"") <= 0);
}
char &String::operator[] (int i)
{
	if((0<=i) && (i<=m_length))
	{
		return m_str[i];
	}
	else
	{
		THROW_EXPECTION(IndexOutofBoundsExpection," the parater i is invalid");
	}
}
char String::operator[](int i)const
{
	return (const_cast<String&>(*this)[i]);
}
String String:: operator + ( const String&s) const
{
	return (*this + s.m_str);
}
String String::operator + ( const char*s) const
{
	String ret;
	int len = m_length + strlen(s?s:"");
	char *str = reinterpret_cast<char *>(malloc(len + 1)); //
	if( str )
	{
		strcpy(str,m_str);
		strcat(str,s?s:"");
		
		free(ret.m_str);
		
		ret.m_str = str;
		
		ret.m_length = len;
	}
	else
	{
		THROW_EXPECTION(NoenoughMemmoryExpection,"No enough memory to creat a m_str");
	}
	return ret;
}
String& String::operator += ( const String&s) 
{
	return (*this = *this+s.m_str );
}
String& String:: operator += ( const char*s) 
{
	return (*this = *this+s );

}

String String::operator - ( const String&s) const
{
	return String(*this).remove(s);
}
String String::operator - ( const char*s) const
{
    return String(*this).remove(s);
}
String& String::operator -= ( const String&s)
{
	return remove(s);
}
String& String::operator -= ( const char*s)
{
	return remove(s);
}

String& String:: operator = ( const String&s) 
{
	return(*this = s.m_str);
}
String& String:: operator = ( const char*s) 
{
	if(m_str != s)
	{
		char *str = _strdup(s?s:"");
		
		if( str )
		{
			free(m_str);
			
			m_str = str;
			m_length = strlen(m_str);
		}
		else
		{
			THROW_EXPECTION(NoenoughMemmoryExpection,"No enough memory to creat a m_str");
		}
		
	}
}
String& String:: operator = ( const char c) 
{
	char s[] = {c, '\0'};
	return (*this=s);
}
}
