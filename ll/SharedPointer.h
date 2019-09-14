#ifndef SHAREDPOINTEWR_HH
#define SHAREDPOINTEWR_HH
#include <cstdlib>
#include "Pointer.h"
#include "expection.h"
namespace DTLib{
	template <typename T>
	class SharedPointer :public Pointer <T>
	{
		protected :
			int *m_ref;
			void assign(const SharedPointer<T>& obj)
			{
				this->m_ref = obj.m_ref;
				this->m_pointer = obj.m_pointer;
				if(this->m_ref)		
				{
					(*this->m_ref)++;
				}		
			} 
			
		public:
			SharedPointer(T *p = NULL):m_ref(NULL)  // 将P指向计数指针m_ref,初始值都为null 
			{
				if( p )
				{
					this->m_ref = static_cast<int*>((std::malloc(sizeof(int))));
					if(this->m_ref)
					{
						*(this->m_ref) = 1;
						this->m_pointer = p;
					}
					else
					{
						THROW_EXPECTION(NoenoughMemmoryExpection,"no enough memory to mslloc...");
					}
				}
			}
			SharedPointer(const SharedPointer<T>& obj) :Pointer<T>(NULL)
			{
				assign(obj);
			}
			SharedPointer<T>&operator = (const SharedPointer<T>&obj)  /* 复制构造函数 */ 
			{
				if(this != &obj)
				{
					clear();//自空 
					assign(obj);

				}
				return *this;
			}
			void clear()
			{
				T*todel = this->m_pointer;
				int *ref = this->m_ref;
				this->m_pointer = NULL;
				this->m_ref = NULL;
				if(ref)
				{
					(*ref)--;
					if(*ref == 0)
					{
						free(ref);
						delete todel;
					}
				}
			}
			~SharedPointer()
			{
				clear();
			}
			
	};
			template <typename T>
			bool operator == (const SharedPointer<T>&l,const SharedPointer<T>&r)
			{
				return(l.get()==r.get());
			}
			template <typename T>
			bool operator != (const SharedPointer<T>&l,const SharedPointer<T>&r)
			{
				return !(l==r);
			}
				
}
#endif //SHAREDPOINTEWR_HH
