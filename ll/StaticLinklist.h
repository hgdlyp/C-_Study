#ifndef STATICLINKLIST_H__
#define STATICLINKLIST_H__
#include"LinkList.h"
namespace DTLib{
	template <typename T,int N>
	class StaticLinklist :public Linklist<T>
	 {
		protected: 
			typedef typename Linklist<T>::Node Node;
			struct SNode :public Node
			{
				void* operator new(size_t size,void *loc) // 重载new操作符
				{
					(void)size;
					return loc;
				}
			}; 
			unsigned char m_space[sizeof(SNode)*N];  //定义一片预留的内存空间 
			int m_used[N]; //用来记录当前内存空间是否被使用
			Node *create() 
			{
				SNode *ret = NULL;
				for(int i = 0;i<N;i++)
				{
					if(!m_used[i])
					{
						ret = reinterpret_cast<SNode *>(m_space) + i;   //强制类型转换 
						ret = new(ret)SNode();
						m_used[i] = 1;
						break;
					}
				}
				return ret;
			 } 
			void destroy(Node *pn)
			{
				SNode *space = reinterpret_cast<SNode*>(m_space);
				SNode *psn = dynamic_cast<SNode*>(pn);  //将父类指针强制转换成子类指针 
				for(int i=0;i<N;i++) 
				{
					if(psn==space +i)
					{
						m_used[i] = 0;
						psn->~SNode();
						break;
					}
				}
			}
		public:
			StaticLinklist()
			{
				for(int i= 0;i<N;i++)
				{
					m_used[i] = 0;
				}
			}
			~StaticLinklist()
			{
				this->clear();
			}
			int capacity()
			{
				return N;
			}
	};
}

#endif //STATICLINKLIST_H__
