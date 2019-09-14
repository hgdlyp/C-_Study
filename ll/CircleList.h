#ifndef  CIRCLELIST_H__
#define CIRCLELIST_H__
#include "LinkList.h"
namespace DTLib{
	template <typename T>
	class CircleList :public Linklist <T>
	{
		protected:
			typedef typename Linklist<T>::Node Node;
			int mod(int i) const 
			{
				return (this->m_length == 0) ? 0 : (i % this->m_length);
			}
			Node *last() const
			{
				return this->position(this->m_length-1)->next;
			}
			void last_to_first()
			{
				last()->next=(this->m_header.next);
			}	
		
		public:
			bool insert(const T&e)
			{
				return insert(this->m_length ,e); //insert the element at the end of this list
			}
			bool insert(int i,const T&e)
			{
				bool ret = true;
				i = mod(i);
				ret = Linklist<T>::insert(i,e);
				if( ret &&(i==0) )
				{
					last_to_first();
				}
				return ret;
			}
			bool remove(int i)
			{
				bool ret = true;
				i = mod(i);
				if(i==0)
				{
					Node *todel = this->m_header.next;
					
					if(todel!=NULL)
					{
						this->m_header.next = todel->next;
						this->m_length--;
						if(this->m_length>0)
						{
							last_to_first();
							if(this->m_current == todel)
							{
								this->m_current = todel->next;
							}
						}
						else
						{
							this->m_header.next = NULL;
							this->m_current = NULL;
						}
						this->destroy(todel);
					}
					else
					{
						ret = false;
					}
				}
				else
				{
					this->Linklist<T>::remove(i);
				}
				return ret;
			}
			bool set( int i,const T&e)
			{
				return Linklist<T>::set(mod(i),e);
			}
			T get(int i) const
			{
				return Linklist<T>::get(mod(i));
			}
			bool get(int i,const T&e) const   //get的重载函数 
			{
				return Linklist<T>::get(mod(i),e);
			}
			int find(const T&e)const
			{
				int ret = -1;
				
				Node *slider = this->m_header.next;
				for( int i= 0;i<this->m_length;i++)
				{
					if(slider->value == e)
					{
						ret = i;
						break;
					}
					slider = slider->next;
				}
				return ret;
			}
			void clear()
			{
				while(this->m_length>1)
				{
					remove(1);
				}
				if(this->m_length ==1)
				{
					Node*todel = this->m_header.next;
					
					this->m_header.next = NULL;
					this->m_length = 0;
					this->m_current = NULL;
					
					this->destroy(todel);
				}
			}
			bool move(int i,int step=1)
			{
				return Linklist<T>::move(mod(i),step);
			}
			bool end()
			{
				return (this->m_length ==0)|| (this->m_current==NULL);//当前链表长度为0且游标指针为空 
			}
			
			~CircleList()
			{
				clear();
			}
	};
}


#endif    //CIRCLELIST_H__
