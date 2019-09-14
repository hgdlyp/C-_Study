#ifndef DYNAMICARRAY_HH__
#define DYNAMICARRAY_HH__
#include "Array.h"
namespace DTLib{
	template <typename T> 
	class DynamicArray :public Array <T>
	{
		protected:
		int m_length;
		T *copy( T *array,int len ,int newlen)  //赋值函数，简化代码 
		{
			T *ret = new T[newlen];
			if(ret !=NULL)
			{
				int size= (len<newlen) ? len :newlen;
				for(int i = 0;i<size; i++)
				{
					ret[i] = array[i]; 
				}
			}
			return ret;
		}
		void update(T *array,int length)
		{
			if(array!=NULL)
			{
				T*temp = this->m_array;
				
				this->m_array = array;
				this->m_length = length;
				delete []temp;
			}
			else
			{
				THROW_EXPECTION(NoenoughMemmoryExpection ," no enough memory ...");

			}
		 } 
		 void init(T *array ,int length)
		 {
		 	if(array !=NULL)
		 	{
		 		this->m_array  = array;
				this->m_length = length;	
			}
			else
			{
				THROW_EXPECTION(NoenoughMemmoryExpection ," no enough memory ...");
			}
		 }
		public:
		 DynamicArray(int length = 0)
		 {
		 	init(new T[length],length);
		 }
		 DynamicArray(const DynamicArray<T> &obj)
			{
				init(copy(obj.m_array,obj.m_length,obj.m_length),obj.m_length);
			}
			DynamicArray<T>&operator = (const DynamicArray<T> &obj)
			{
				if( this != &obj)
				{
					update(copy(obj.m_array ,obj.m_length,obj.m_length),obj.m_length);
				} 
				return *this;
			}
			int length() const
			{
				return m_length;
			}
			void resize(int length)
			{
				if(length != this-> m_length)
				{
					update(copy(this->m_array,this->m_length,length),length);
				}
			}
			~DynamicArray()
			{
				delete [] this->m_array;
			}
	};
}

#endif
