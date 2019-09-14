#ifndef DUALLINKLIST_HH__
#define DUALLINKLIST_HH__
#include "expection.h"
#include"List.h"
namespace DTLib{
	template <typename T>
	class DualLinkList :public List<T>
	{
		protected:
			struct Node :public Object{
				T value;
				Node *next;
				Node *pre;
			};
		    mutable struct :public Object{   //要继承顶层父类 
	        	char reserved[sizeof(T)];    //分配一个固定空间 
	        	Node* next;
	    	    Node *pre;
			} m_header;
			int m_length;
			int m_step;
			Node* m_current; 
			Node *position(int i) const
			{
				Node *ret = reinterpret_cast<Node*>(&m_header); //强制类型转换 
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
			DualLinkList() //构造函数即是对类中数据元素的初始化 
			{
				m_header.next = NULL;
				m_header.pre = NULL;
				m_length = 0; 
				m_step = 1;  //默认移动次数为1 
				m_current = NULL;
			}
			bool insert(const T&e)//默认直接向线性表标的尾部插入元素。 
			{
				return insert(m_length,e);
			}
		    bool insert( int i,const T&e) 
			{
				bool ret = ((0<=i) && (i<=m_length));
				if( ret )
				{
					Node *node = create();  //创建一个新节点 
					if(node != NULL)
					{
						Node *current = position(i);
						Node *next = current->next;
						node->value = e;
						
						node->next = next;
						current->next = node;
						if(current !=reinterpret_cast<Node *>(&m_header))   //current 指针不等于头结点
						{
							node ->pre = current; 
						} 
						else
						{
							node ->pre = NULL;
						}
						if(next !=NULL)  // 是否是最后一个节点 
						{
							next->pre = node;
						}
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
						Node *next = todel->next;
						if(m_current == todel)
						{
							m_current = next;
						}
						current->next = next;
						if(next!=NULL)
						{
							next->pre = todel->pre;
						}
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
				while(m_length > 0)
				{
					remove(0);
				}
				
			}
			bool move(int i,int step = 1)  // 默认每次移动的次数为1
			{
				bool ret = (0<=i) && (i<=m_length) && (step>0);
				if( ret )
				{
		 			m_current = position(i)->next; //将游标移动到指定的位置
					m_step = step;   //记录每次移动的次数 
				}
				return ret; 
			} 
			bool end()
			{
				return ( m_current == NULL );
			} 
			T current()
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
			 bool next()
			{
		    	int i = 0;
			 	while ( !end() && (i<m_step))//还没到达链表的尾部 
					{
					    m_current = m_current->next;
					    i++;
					}
				return (i==m_step);
			}
			bool pre()
			{
				int i = 0;
			 	while ( !end() && (i<m_step))//还没到达链表的尾部 
					{
					    m_current = m_current->pre;
					    i++;
					}
				return (i==m_step);
			}
			~DualLinkList()
			{
				clear();
			}
	}; 
}


#endif
