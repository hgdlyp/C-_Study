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
				void* operator new(size_t size,void *loc) // ����new������
				{
					(void)size;
					return loc;
				}
			}; 
			unsigned char m_space[sizeof(SNode)*N];  //����һƬԤ�����ڴ�ռ� 
			int m_used[N]; //������¼��ǰ�ڴ�ռ��Ƿ�ʹ��
			Node *create() 
			{
				SNode *ret = NULL;
				for(int i = 0;i<N;i++)
				{
					if(!m_used[i])
					{
						ret = reinterpret_cast<SNode *>(m_space) + i;   //ǿ������ת�� 
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
				SNode *psn = dynamic_cast<SNode*>(pn);  //������ָ��ǿ��ת��������ָ�� 
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
