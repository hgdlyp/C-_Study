#ifndef LINKSTACK_H_
#define LINKSTACK_H_
#include "Stack.h"
#include "LinkList.h"
#include "expection.h"
namespace DTLib{
	template <typename T>
	class LinkStack : public Stack<T>{
		protected:
		Linklist <T> m_list;
		public:
			void push(const T &e)
			{
				m_list.insert(0,e);
			}
			void pop()
			{
				if(m_list.length()>0)
				{
					m_list.remove(0);
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection," no element in this stack...");
				}
			}
			T top() const
			{
				if(m_list.length()>0)
				{
					return m_list.get(0);
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection," no element in this stack...");
				}
			}
			void clear()
			{
				m_list.clear();
			}
			int size()const
			{
				return m_list.length();
			}
	};
}

#endif //LINKSTACK_H_


