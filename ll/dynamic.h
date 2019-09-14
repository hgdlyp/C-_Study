#ifndef DYNAMICLIST__H__
#define DYNAMICLIST__H__
#include"SeqList.h"
#include"expection.h"
namespace DTLib{
	template <typename T>
	class DynamicList :public SeqList <T>
	{
		protected:
			int m_capacity;
		public:
			DynamicList(int capacity) //����ռ�
			{
				this ->m_array = new T[capacity];
				if(this ->m_array != NULL) 
				{
					this->m_length = 0;  /*����Ա��������ֵ */
					this->m_capacity = capacity;
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection," no enough emmory to create dynamic obj");
				}
			} 
			int capacity () const 
			{
				return m_capacity;
			}
			void resize(int capacity)
			{
				if(capacity != m_capacity)
				{
					T*array = new T[capacity];
					if(array !=NULL)
					{
						int length = ( this->m_length < capacity ? this->m_length : capacity );
					for( int i=0;i<length;i++)
					{
						array[i] = this->m_array[i]; 
					}
						T *temp = this->m_array;
						this->m_array    = array;
						this->m_capacity = capacity;

				    }
				    else
				    {
				    	THROW_EXPECTION(NoenoughMemmoryExp						this->m_length   = length;
						delete []temp;ection," no enough emmory to create dynamic obj");

					}
		        } 
	    	}
			~DynamicList()  //�ͷſռ� 
			{
				delete [] this->m_array;
			}
	};
}


#endif //DYNAMATICLIST__H__
