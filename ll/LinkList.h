#ifndef LINK_LIST_H__
#define LINK_LIST_H__
#include "List.h"
#include "expection.h"
namespace DTLib{
	template <typename T>
	class Linklist : public List<T>{
		protected:
			struct Node :public Object{
				T value;
				Node* next;
			};
		    mutable struct :public Object{   //Ҫ�̳ж��㸸�� 
		    	char reserved[sizeof(T)];
		    	Node* next;
			} m_header;
			int m_length;
			int m_step;
			Node* m_current; 
			Node *position(int i) const
			{
				Node *ret = reinterpret_cast<Node*>(&m_header); //ǿ������ת�� 
				for(int p = 0;p<i;p++)
				{
					ret = ret->next;
				}
				return ret;
			}
			virtual Node* create()
			{
				return new Node();
			}
			virtual void destroy(Node *pn)
			{
				delete pn;
			}
		public:
			Linklist() //���캯�����Ƕ���������Ԫ�صĳ�ʼ�� 
			{
				m_header.next = NULL;
				m_length = 0; 
				m_step = 1;  //Ĭ���ƶ�����Ϊ1 
				m_current = NULL;
			}
			bool insert(const T&e)//Ĭ��ֱ�������Ա���β������Ԫ�ء� 
			{
				return insert(m_length,e);
			}
		    bool insert( int i,const T&e) 
			{
				bool ret = ((0<=i) && (i<=m_length));
				if( ret )
				{
					Node *node = create();
					if(node != NULL)
					{
						Node *current = position(i);
						node->value = e;
						node->next = current->next;
						current->next = node;
						m_length ++;	
					} 
					else
					{
						THROW_EXPECTION(NoenoughMemmoryExpection ," no enough memory to insert new elem");
					}	
				}
				return ret;	
			}
		    bool remove( int i) 
		    {
		    	bool ret = ((0<=i) && (i<=m_length));
		    	if( ret )
		    	{
		    			Node *current = position(i);
						Node *todel = current->next;
						if(m_current == todel)
						{
							m_current = todel->next;
						}
						current->next = todel->next;
						m_length --;
						
						destroy(todel);
						
					
				}
				return ret;

			}
			 bool set( int i, const T&e)	
			{
				bool ret = ((0<=i) && (i<=m_length));
		    	if( ret )
		    	{
					position(i)->next->value = e;
		    	}
		    	return ret;
		    	
			}
			virtual T get (int i) const
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
			virtual bool get( int i, T&e) const
			{
				bool ret = ((0<=i) && (i<=m_length));
		    	if( ret )
		    	{
					e = position(i)->next->value;
		    	}
		    	return ret;
		    	
			}
			int find(const T &e) const
			{
				int ret = -1;
				int i = 0;
				Node *node = m_header.next;
				while(node)
				{
					if(node->value == e)
					{
						ret = i;
						break;
					}
					else
					{
						node = node->next;
						i++;
					}
				}
				return ret;
			}
			 int  length() const
			{
				return m_length;
			}
			 void clear () 
			{
				while(m_header.next)
				{
					Node *todel = m_header.next;
					m_header.next = todel->next;
					m_length = 0 ;
					destroy(todel);
				}
				
			}
		virtual	bool move(int i,int step = 1)  // Ĭ��ÿ���ƶ��Ĵ���Ϊ1
			{
				bool ret = (0<=i) && (i<=m_length) && (step>0);
				if( ret )
				{
		 			m_current = position(i)->next; //���α��ƶ���ָ����λ��
					m_step = step;   //��¼ÿ���ƶ��Ĵ��� 
				}
				return ret; 
			} 
		virtual	bool end()
			{
				return ( m_current == NULL );
			} 
		virtual	T current()
			{
				if(!end())
				{
					return m_current->value;
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection," no value at m_current");
				} 
			}
		virtual bool next()
			{
		    	int i = 0;
			 	while ( !end() && (i<m_step))//��û���������β�� 
					{
					    m_current = m_current->next;
					    i++;
					}
				return (i==m_step);
			}
			~Linklist()
			{
				clear();
			}
	};
	
}

#endif
