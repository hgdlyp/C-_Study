#ifndef LINKQUEUE_H__
#define LINKQUEUE_H__
#include "Queue.h"
#include "LinuxList.h"
#include "expection.h"
namespace DTLib{
	template <typename T>
	class LinkQueue : public Queue<T>{
		protected:
			struct Node :public Object{
				list_head head;
				T value;
			};
			list_head m_header;
			int m_length;
		public:
			LinkQueue()
			{
				m_length = 0;
				
				INIT_LIST_HEAD(&m_header);
			}
			void add(const T &e)
			{
				Node *node = new Node();
				if(node!=NULL)
				{
					node->value = e;
					list_add_tail(&node->head,&m_header);
					m_length ++;
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection,"no space at current queue...");
				}
			}
			void remove()
			{
				if(m_length > 0)
				{
					list_head *todel = m_header.next;
					list_del(todel);
					m_length--;
					delete list_entry(todel,Node,head);
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection,"this current queue has no elem...");
				}
			}
			T front()const
			{
				if(m_length > 0)
				{
					return list_entry(m_header.next,Node,head)->value;
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection,"this current queue has no elem...");
				}
			}
			void clear()
			{
				while(m_length >0)
				{
					remove();
				}
			}
			int length()const
			{
				return m_length;
			}
				
	};
}


#endif //LINKQUEUE_H__
