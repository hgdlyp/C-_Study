#ifndef TREENODE__
#define TREENODE__
#include "Object.h"
namespace DTLib{
	template <typename T>
	class TreeNode :public Object{
		protected :
		TreeNode (const TreeNode<T> &);
		TreeNode<T> &operator = (const TreeNode<T>&);
		bool m_flag;  //��¼�����Ŀռ��Ƿ��ڶѿռ� ������� 
		void * operator new(size_t size) throw()
		{
			return Object::operator new(size);
		}
	public:
		T value;
		TreeNode<T> *parent;
		TreeNode()
		{
			m_flag = false;
			parent = NULL;
		}
	    
		bool flag()
		{
			return m_flag;
		}
		virtual ~TreeNode() = 0;
}; 
	template < typename T>
	TreeNode<T>::~TreeNode()
	{
		
	}
}

#endif  //TREENODE__
