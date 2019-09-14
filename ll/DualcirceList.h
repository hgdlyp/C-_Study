#ifndef DUALCIRCLELIST_H__
#define DUALCIRCLELIST_H__
#include "LinuxList.h"
#include "DualLinklist.h"
namespace DTLib
{
	template <typename T>
	class DualcircleList : public DualLinkList<T>
	{
	protected:
		struct Node : public Object{
			list_head head;
			T value;
		};	
		list_head m_header;
		list_head * m_current;
		list_head *position(int i) const   //��λ���� 
		{
			list_head *ret = const_cast<list_head *>(&m_header);
			for(int p=0;p<i;p++)   //��λ��i���ڵ�λ�� 
			{
				ret = ret->next;
			}
			return ret;
		}
		int mod(int i) const 
		{
			return (this->m_length == 0) ? 0 : (i%this->m_length);
		}
	public:
	 	DualcircleList()  //���캯�����Ƕ�һЩ��Ա�������г�ʼ�� 
	 	{
	 		this->m_length = 0;
	 		this->m_step = 1;
	 		
	 		m_current = NULL;
	 		
	 		INIT_LIST_HEAD(&m_header);
		 }
		 bool insert(const T &e)
		 {
		 	return insert(this->m_length,e);
		 }
		 bool insert(int i,const T &e) 
		 {
		 	bool ret = true;
		 	Node *node  = new Node();
		 	
		 	i = i%(this->m_length +1);
		 	
		 	if(node !=NULL)
		 	{
		 		 node->value = e;
				 list_add_tail(&node->head,this->position(i)->next);  //��β����������Ԫ�� 
				 this->m_length++;
			} 
			else
			{
				THROW_EXPECTION(NoenoughMemmoryExpection ," no enough memory to insert new elem");
			}
			return ret;
		}
		bool remove(int i)
		{
			bool ret = true;
			i = mod(i);
			ret = ((0<=i)&&(i<this->m_length)) ;
			if(ret)
			{
				list_head* todel = position(i)->next;
				if(m_current == todel)
				{
					m_current = todel->next;
				}
				list_del(todel);
				this->m_length--;
				
				delete list_entry(todel,Node,head);
			}
			return ret;
		} 
		bool set( int i, const T&e)	
			{
				bool ret = true;
				i = mod(i);
				ret = ((0<=i) && (i<=this->m_length));
		    	if( ret )
		    	{
					list_entry(position(i)->next,Node,head)->value = e;
		    	}
		    	return ret;
		    	
			}
			 T get (int i) const
			{
				T ret;
				if(get( i, ret))
				{
					return ret;
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection ," no enough memory to insert new elem");
				}
			}
			 bool get( int i, T&e) const
			{
				bool ret = true;
				i = mod(i);
				ret = ((0<=i)&&(i<this->m_length)) ;
		    	if( ret )
		    	{
					e = list_entry(position(i)->next,Node,head)->value;
		    	}
		    	return ret;
		    	
			}
			int find(const T &e) const	
			{
				int ret = -1;
				int i = 0;
				list_head *slider = NULL;
				
				list_for_each(slider,&m_header)
				{
					if(list_entry(slider,Node,head)->value == e)
					{
						ret = i;
						break;
					}
					i++;
				}
				return ret;		
		    }
			int length()const
			{
				return this->m_length;
		    }
			void clear()
			{
				while(this->m_length >0)
				{
					remove(0);
				}		
		    }	 
		    bool move(int i,int step = 1)
		    {
		    	bool ret = (step>0);
		    	i=mod(i);
		    	ret = ret && (0<=i) &&(i<this->m_length);
		    	if(ret)
		    	{
		    		m_current = position(i)->next;
		    		
		    		this->m_step = step;
				}
				return ret;
			}
			bool end()
			{
				return ( m_current == NULL ) || (this->m_length == 0);
			} 
			T current()
			{
				if(!end())
				{
					return list_entry(m_current,Node,head)->value;
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection," no value at m_current");
				} 
			}
			 bool next()
			{
		    	int i = 0;
			 	while ( !end() && (i<this->m_step))//��û���������β�� 
					{
						if(m_current != &m_header)
						{
							m_current = m_current->next;
					    	i++;
						}
						else
						{
							m_current = m_current->next;
						}
					}
					if(m_current == &m_header)
					{
						m_current = m_current->next;
					}
				return (i==this->m_step);
			}
			bool pre()
			{
				int i = 0;
			 	while ( !end() && (i<this->m_step))//��û���������β�� 
					{
						if(m_current != &m_header)   //�ж��Ƿ����ͷ��㣬����������� 
						{
							m_current = m_current->prev;
					    	i++;
						}
						else
						{
							m_current = m_current->prev;
						}
					}
					if(m_current == &m_header)
					{
						m_current = m_current->prev;
					}
				return (i==this->m_step);
			}
			~DualcircleList()
			{
				clear();	
			 } 
	};
	
}


#endif  //DUALCIRCLELIST_H__
