#ifndef STATICQUEUE_H__
#define STATICQUEUE_H__
#include "Queue.h"
#include "expection.h"
namespace DTLib{
	template <typename T,int N>
	class StaticQueue :public Queue<T>{
		protected:
			T m_space[N];
			int m_front;
			int m_rear;
			int m_length;
		public:
			StaticQueue()
			{
				m_front  = 0;
				m_rear   = 0;
				m_length = 0;
			}
			int capacity() const
			{
				return N;
			}
			void add(const T &e)
			{
				if( m_length <N)
				{
					m_space[m_rear] = e;
					m_rear = (m_rear +1)%N;  //实现循环计数
					m_length ++; 
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection,"no space at current queue...");
				}
			}
			void remove()
			{
				if(m_length>0)
				{
					m_front = (m_front + 1) %N;
					m_length -- ;
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
					return m_space[m_front];
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection,"this current queue has no elem...");
				}
			}
			void clear()
			{
				m_front  = 0;
				m_rear   = 0;
				m_length = 0;
			}
			int length()const
			{
				return N;
			}
	};
}

#endif //STATICQUEUE_H__
