#ifndef GTreeNode_H_
#define GTreeNode_H_
#include "TreeNode.h"
#include "LinkList.h"
namespace DTLib{
	template <typename T>
	class GTreeNode : public TreeNode<T>
	{	
		public:
			Linklist <GTreeNode<T>*> child;
			static GTreeNode<T> *NewNode()
			{
				GTreeNode<T> * ret =  new GTreeNode<T>();
				if( ret != NULL)
				{
					ret->m_flag = true;
				}
				return ret;
			}
	};
}
#endif //GTreeNode_H_

