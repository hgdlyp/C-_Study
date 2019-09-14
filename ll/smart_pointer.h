#ifndef SMART_POINTER__
#define SMART_POINTER__
#include "Pointer.h"
namespace DTLib{
	template <typename T>
	class Smart_Pointer:public Pointer<T>{      /* ����ָ����ģ�� */ 
		public :
			Smart_Pointer( T *p = NULL) : Pointer<T>(p) /* ��Ա����*/ 
			{
			}
			Smart_Pointer(const Smart_Pointer<T>& obj)
			{
				this->m_pointer = obj.m_pointer;
				const_cast < Smart_Pointer<T>& >(obj).m_pointer = NULL;
				
			}
			Smart_Pointer<T>&operator = (const Smart_Pointer<T> &obj)  /* ���ƹ��캯�� */ 
			{
				if (this != obj.m_pointer)  //�ж��Ƿ����Է�ֵ 
				{
					T *p = this->m_pointer;
					this->m_pointer = obj.m_pointer;
					const_cast <Smart_Pointer<T> & >(obj).m_pointer = NULL;
					delete p;
				}
				return *this;   //��������֧���ظ���ֵ 
			}
			
			~Smart_Pointer()
			{
				delete this->m_pointer;
			}
			 
		};
		
}

#endif /* SMART_POINTER__ */
