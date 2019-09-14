#ifndef STRING_H
#define STRING_H
#include "Object.h"
namespace DTLib
{
	class String :public Object
	{
		protected:
			char *m_str;
			int m_length;
			
			void init(const char *s);
			bool equal(const char *l,const char *r,int len)const;
			
			static int *make_pmt(const char *p) ;
			static int kmp(const char *soc,const char *dest) ;
		public:
			String();
			String( char c);
			String( char *s);
			String ( const String &s);
			int length() const;
			const char *str() const; 
			bool startwith(const char *s) const;
			bool startwith(const String&s)const;
			bool endof(const char *s) const;
			bool endof(const String&s)const;
			int indexof(const char *s)const;
			int indexof(const String&s)const;
			
			String& remove(int i,int len);
			String& remove(const char *s);
			String& remove(const String&s);
			
			String& replace(const char *t,const char *s);
			String& replace(const String&t,const char *s);
			String& replace(const char *t, const String&s);
			String& replace(const String&t, const String&s);
			
			String sub(int i,int len);
			
			String &insert( int i,const char *s);
			String &insert(int i,String&s);
			String &trim();  //È¥µô×Ö·û´®Á½¶ËµÄ¿Õ°××Ö·û
			/* ²Ù×÷·ûÖØÔØº¯Êý */
			bool operator == ( const String&s ) const;
			bool operator == ( const char *s) const;
			bool operator != ( const String&s ) const;
			bool operator != ( const char *s) const;
			bool operator >  ( const String&s ) const;
			bool operator >  ( const char *s) const;
			bool operator <  ( const String&s ) const;
			bool operator <  ( const char *s) const;
			bool operator >= ( const String&s ) const;
			bool operator >= ( const char *s) const;
			bool operator <= ( const String&s ) const;
			bool operator <= ( const char *s) const;
			char &operator [] (int i);
			char operator[](int i)const;
			String operator + ( const String&s) const;
			String operator + ( const char*s) const;
			String& operator += ( const String&s);
			String& operator += ( const char*s);
			
			String operator - ( const String&s) const;
			String operator - ( const char*s) const;
			String& operator -= ( const String&s);
			String& operator -= ( const char*s);
			
			String& operator = ( const String&s) ;
			String& operator = ( const char*s) ;
			String& operator = ( const char c) ;
			
		~String();
	};
}


#endif
