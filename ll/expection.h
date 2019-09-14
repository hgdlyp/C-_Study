#ifndef __EXPECTION__
#define __EXPECTION__
#include "Object.h"
namespace DTLib{
#define THROW_EXPECTION(e,m) throw(e(m, __FILE__, __LINE__)) 
	class Expection:public Object{
		protected:
			char *m_message;
			char *m_location;
		    void init (const char *message,const char *file,int line);
		public:
			Expection(const char *message);
			Expection(const char *file, int line);
			Expection(const char *message,const char *file,int line);
			
			Expection(const Expection &e);
			Expection & operator = (const Expection &e );
			
			virtual const char *message() const;
			virtual const char *location() const;
			
			//virtual ~Expection() = 0;
			virtual ~Expection() ;
	};
	class ArithmeticExpection:public Expection{
		public:
		ArithmeticExpection() :Expection(0){}
		ArithmeticExpection(const char*message) : Expection(message){}
		ArithmeticExpection(const char *file ,int line) : Expection(file,line){}
		ArithmeticExpection(const char *message, char *file,int line) : Expection(message,file,line){}
		ArithmeticExpection(const ArithmeticExpection &e):Expection(e){}
		ArithmeticExpection &operator =(const ArithmeticExpection &e)
		{
			Expection::operator = (e);
			return *this ;
		}
	};
	class NullPointerExpection: public Expection{
		public:
		NullPointerExpection() : Expection(0){}
		NullPointerExpection(const char*message) : Expection(message){}
		NullPointerExpection(const char *file ,int line) : Expection(file,line){}
		NullPointerExpection(const char *message, char *file,int line) : Expection(message,file,line){}
		NullPointerExpection(const NullPointerExpection &e):Expection(e){}
		NullPointerExpection &operator =(const NullPointerExpection &e)
		{
			Expection::operator = (e);
			return *this ;
		}
	};
	class IndexOutofBoundsExpection: public Expection{
		public:
		IndexOutofBoundsExpection() : Expection(0){}
		IndexOutofBoundsExpection(const char*message) : Expection(message){}
		IndexOutofBoundsExpection(const char *file ,int line) : Expection(file,line){}
		IndexOutofBoundsExpection(const char *message, char *file,int line) : Expection(message,file,line){}
		IndexOutofBoundsExpection(const IndexOutofBoundsExpection &e):Expection(e){}
		IndexOutofBoundsExpection &operator =(const IndexOutofBoundsExpection &e)
		{
			Expection::operator = (e);
			return *this ;
		}
	};
	class NoenoughMemmoryExpection: public Expection{
	public:
	NoenoughMemmoryExpection() : Expection(0){}
	NoenoughMemmoryExpection(const char*message) : Expection(message){}
	NoenoughMemmoryExpection(const char *file ,int line) : Expection(file,line){}
	NoenoughMemmoryExpection(const char *message, char *file,int line) : Expection(message,file,line){}
	NoenoughMemmoryExpection(const NoenoughMemmoryExpection &e):Expection(e){}
	NoenoughMemmoryExpection &operator =(const NoenoughMemmoryExpection &e)
	{
		Expection::operator = (e);
		return *this ;
	}
	};
	class InvalidParameterExpection: public Expection{
	public:
	InvalidParameterExpection() : Expection(0){}
	InvalidParameterExpection(const char*message) : Expection(message){}
	InvalidParameterExpection(const char *file ,int line) : Expection(file,line){}
	InvalidParameterExpection(const char *message, char *file,int line) : Expection(message,file,line){}
	InvalidParameterExpection(const InvalidParameterExpection &e):Expection(e){}
	InvalidParameterExpection &operator =(const InvalidParameterExpection &e)
	{
		Expection::operator = (e);
		return *this ;
	}
	};
	
}

#endif /*__EXPECTION__*/
