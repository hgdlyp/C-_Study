#ifndef SMART_POINTER__
#define SMART_POINTER__
#include "Pointer.h"
namespace DTLib{
	template <typename T>
	class Smart_Pointer:public Pointer<T>{      /* 智能指针类模板 */ 
		public :
			Smart_Pointer( T *p = NULL) : Pointer<T>(p) /* 成员函数*/ 
			{
			}
			Smart_Pointer(const Smart_Pointer<T>& obj)
			{
				this->m_pointer = obj.m_pointer;
				const_cast < Smart_Pointer<T>& >(obj).m_pointer = NULL;
				
			}
			Smart_Pointer<T>&operator = (const Smart_Pointer<T> &obj)  /* 复制构造函数 */ 
			{
				if (this != obj.m_pointer)  //判断是否是自幅值 
				{
					T *p = this->m_pointer;
					this->m_pointer = obj.m_pointer;
					const_cast <Smart_Pointer<T> & >(obj).m_pointer = NULL;
					delete p;
				}
				return *this;   //这样才能支持重复赋值 
			}
			
			~Smart_Pointer()
			{
				delete this->m_pointer;
			}
			 
		};
		
}

#endif /* SMART_POINTER__ */
