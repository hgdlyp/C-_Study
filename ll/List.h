#ifndef LIST_H
#define LIST_H
#include"Object.h"
namespace DTLib{
template <typename T>
	class List :public Object
	{
		protected:
			List (const List&);        // 禁止拷贝构造赋值操作 ，防止重新指向堆空间 
			List &operator = (const List&);  //操作符重载函数
	public:
		List()
		{
		}   //手工添加构造函数，编译器就不会自己添加构造函数。 
		virtual bool insert(const T&e) = 0; //默认直接向线性表标的尾部插入元素。 
		virtual bool insert( int i,const T&e) = 0;
		virtual bool remove( int i) = 0;
		virtual bool set( int i, const T&e)	= 0;
		virtual bool get( int i, T&e) const = 0;
		virtual int  find(const T &e) const = 0; 
		virtual int  length() const = 0;
		virtual void clear () = 0;
	};

}

#endif  /* LIST_H */
