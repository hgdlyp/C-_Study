#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include "BTreeNode.h"
#include "LinkQueue.h"
#include "DynamicArray.h"
namespace DTLib{
	enum BTTraversal{
		PreOrder,
		InOrder,
		PostOrder,
		LevelOrder
	};
	template <typename T>
	class BTree :public Tree<T>{		
		protected:
			LinkQueue<BTreeNode<T>*> m_queue;
			virtual BTreeNode<T>* find(BTreeNode<T>* node, const T & value) const
			{
				BTreeNode<T>*ret  = NULL;
				if( node != NULL)
				{
					if(node->value == value)
					{
						ret = node;
					}
					else
					{
						if( ret == NULL)
						{
							ret = find(node->left,value);
						}
						if (ret == NULL)
						{
							ret = find(node->right, value);
						}
					}
				}
				return ret;
			}
			virtual BTreeNode<T>* find(BTreeNode<T>* node, BTreeNode<T>* obj) const 
			{
				BTreeNode<T>* ret = NULL;
				if( node == obj )
				{
					ret = node;
				}
				else
				{
					if( node != NULL)
					{
						if( ret == NULL)
						{
							ret = find(node->left,obj);
						}
						if(ret == NULL)
						{
							ret = find(node->right,obj);
						}
					}
				}
				return ret;
			}
			virtual bool insert(BTreeNode<T>* n,BTreeNode<T>* np,BTreeNodePos pos)  //实现确定要插入节点位置的插入函数 
			{
				bool ret = true;
				
				if(pos == ANY)
				{
					if(np->left==NULL)
					{
						np->left = n;
					}
					else if( np->right == NULL)
					{
						np->right = n;
					}
					else
					{
						ret = false;
					}
				}
				else if( pos == LEFT)
				{
					if(np->left == NULL)
					{
						np->left = n;
					}
					else
					{
						ret = false;
					}
				}
				else if( pos == RIGHT)
				{
					if(np->right == NULL)
					{
						np->right = n;
					}
					else
					{
						ret = false;
					}
				}
				else
				{
					ret = false;
				}
				return ret;
			}
			virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
			{
				ret = new BTree();
				if (ret == NULL)
				{
					THROW_EXPECTION(NoenoughMemmoryExpection, " No enough memory to new a BTreeNode...");
				}
				else
				{
					if ( node == root())
					{
						this->m_root = NULL;
					}
					else
					{
						BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(node->parent);
						if (parent->left == node)
						{
							parent->left = NULL;
						}
						else if (parent->right == node)
						{
							parent->right = NULL;
						}
						node->parent = NULL;

					}
					ret->m_root = node;
				}
			}
			virtual void free(BTreeNode<T> * node)
			{
				if (node != NULL)
				{
					free(node->left);
					free(node->right);
					if (node->flag())
					{
						delete node;
					}
				}
			}
			int count(BTreeNode<T>*node) const
			{
				int ret = 0;
			    ret = (node != NULL) ? ((count(node->left) + count(node->right)) + 1) : 0;
				return ret;
			}
			int height(BTreeNode<T>*node) const
			{
				int ret = 0;
				if (node != NULL)
				{
					int lh = height( node->left );
					int rh = height( node->right );
					ret = ((lh > rh) ? lh : rh )+1;  //递归回溯哈哈
				}
				return ret;
			}
			int degree(BTreeNode<T>* node) const
			{
				int ret = 0;
				if (node != NULL)
				{
					BTreeNode<T>* child[] = { node->left, node->right };
					ret = (!!node->left + !!node->right);
					for (int i = 0; (i < 2) && (ret < 2); i++)
					{
						int d = degree(child[i]);
						if (ret < d)
						{
							ret = d;
						}
					}
				}

				/*ret = (!!node->left + !!node->right);  //当两个节点指针都不为空时 ret = 2

				if (ret < 2)      //判断当前树的节点是否已经为2，
				{
				int dl = degree(node->left);
				if (ret < dl)
				{
				ret = dl;
				}
				}
				if (ret < 2)
				{
				int dr = degree(node->right);
				if (ret < dr)
				{
				ret = dr;
				}*/

				return ret;
			}
				//另一种效率不高的写法
				/*if (node!= NULL)
				{
					int dl = degree(node->left);
					int dr = degree(node->right);

					ret = (!!node->left + !!node->right);
					if (ret < dl)
					{
						ret = dl;
					}
					if (ret < dr)
					{
						ret = dr;
					}
				}*/
			void PreOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> & queue)
			{
				if (node != NULL)
				{
					queue.add(node);
					PreOrderTraversal(node->left, queue);
					PreOrderTraversal(node->right, queue);
				}
			}
			void InOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)
			{
				if (node != NULL)
				{
					InOrderTraversal(node->left, queue);
					queue.add(node);
					InOrderTraversal(node->right, queue);
				}
			}
			void PostOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*>& queue)  //每访问一个节点就将该节点压入队列中
			{
				if (node != NULL)
				{
					PostOrderTraversal(node->left, queue);
					PostOrderTraversal(node->right, queue);
					queue.add(node);
				}
			}
			void LevelOrderTraversal(BTreeNode<T>* node, LinkQueue<BTreeNode<T>*> & queue)   //层次遍历二叉树实现函数
			{
				if (node != NULL)
				{
					LinkQueue<BTreeNode<T>*> tmp;

					tmp.add(node);
					while ( tmp.length() > 0)  //实现了不断向两个对列中压入数据元素
					{
						BTreeNode<T> *n = tmp.front();
						if (n->left != NULL)
						{
							tmp.add(n->left);
						}
						if (n->right != NULL)
						{
							tmp.add(n->right);
						}
						tmp.remove();
						queue.add(n);
					}
				}
				
			}
			BTreeNode<T> *clone(BTreeNode<T> *node) const
			{
				BTreeNode<T> *ret = NULL; 

				if (node != NULL)
				{
					ret = BTreeNode<T>::NewNode();
					if (ret == NULL)
					{
						THROW_EXPECTION(NoenoughMemmoryExpection, " No enough memory to new a clone ret...");
					}
					else
					{
						ret->value = node->value;
						ret->left = clone(node->left);
						ret->right = clone(node->right);

						if (ret->left != NULL)
						{
							ret->left->parent = ret;
						}
						if (ret->right != NULL)
						{
							ret->right->parent = ret;
						}
					}

					
				}
				return ret;
			}
			bool equal(BTreeNode <T>*lh, BTreeNode<T>*rh)
			{
				if (lh == rh)
				{
					return true;
				}
				else if ((lh != NULL) && (rh != NULL))
				{
					return (lh->value == rh->value) && (equal(lh->left,rh->left)) && (equal(lh->right,rh->right));  //比较节点值比较左右子树
				}
				else
				{
					return true;
				}
			}
			BTreeNode<T> *add(BTreeNode<T> *lh, BTreeNode<T> *rh) const
			{
				BTreeNode<T> * ret = NULL;
				if ((lh == NULL) && (rh != NULL))
				{
					ret = clone(rh);
				}
				else if ((lh != NULL) && (rh == NULL))
				{
					ret = clone(lh);
				}
				else if ((lh != NULL) && (rh != NULL))  //要加上此语句否则当两个指针都为空时也会跳转到这里
				{
					ret = BTreeNode<T>::NewNode();
					if (ret != NULL)
					{
						ret->value = lh->value + rh->value;
						ret->left = add(lh->left, rh->left);
						ret->right = add(lh->right, rh->right);
						if (ret->left != NULL)
						{
							ret->left->parent = ret;
						}
						if (ret->right != NULL)
						{
							ret->right->parent = ret;
						}
					}
					else
					{
						THROW_EXPECTION(NoenoughMemmoryExpection, " No enough memory to new a BTreeNode ret...");
					}
				}
				return ret;
			}
			void traversal(BTTraversal order, LinkQueue<BTreeNode<T>*> queue)
			{
				switch (order)
				{
				case PreOrder:
					PreOrderTraversal(root(), queue);
					break;
				case InOrder:
					InOrderTraversal(root(), queue);
					break;
				case PostOrder:
					PostOrderTraversal(root(), queue);
					break;
				case LevelOrder:
					LevelOrderTraversal(root(), queue);
					break;
				default:
					THROW_EXPECTION(InvalidParameterExpection, "paramtor order is invalid...");
					break;
				}
			}
			BTreeNode<T>*connect(LinkQueue<BTreeNode<T>*> & queue)
			{
				BTreeNode<T>* ret = NULL;
				if (queue.length() > 0)
				{
					ret = queue.front();
					BTreeNode<T>* slider = queue.front();
					queue.remove();
					slider->left = NULL;

					while (queue.length() > 0)
					{
						slider->right = queue.front();
						queue.front()->left = slider;
						slider = queue.front();
						queue.remove();
					}
					slider->right = NULL;
				}
				return ret;
			}
		public:
			 bool insert(TreeNode<T> *node)
			 {
			 	return insert(node,ANY);
			 }
			 virtual bool insert(TreeNode<T> *node,BTreeNodePos pos)
			 {
			 	bool ret = true;
			 	if( node != NULL )
			 	{
			 		if( this->m_root == NULL)
			 		{
			 			this->m_root = node;
			 			node->parent = NULL;
					}
					else
					{
						BTreeNode<T> *np = find(node->parent);
						if( np != NULL)
						{
							ret = insert(dynamic_cast<BTreeNode <T>*>(node),np,pos);
						}
						else
						{
							THROW_EXPECTION(InvalidParameterExpection,"node's parent  is not in this Btree ");
						}
					}
					return ret;
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection,"node is can not be NULL...");
				}
			 }
			 bool insert(const T& value,TreeNode<T> *parent) 
			 {
			 	return insert(value,parent,ANY);
			 }
			 virtual bool insert(const T& value,TreeNode<T> *parent,BTreeNodePos pos)  //为啥是虚函数呢
			 {
			 	bool ret = true;
			 	BTreeNode<T>* node = BTreeNode<T>::NewNode();
			 	if( node !=NULL )
			 	{
					node->value = value;
					node->parent = parent;
					
					ret = insert(node,pos);
					if(!ret)
					{
						delete node;
					}
				}
				 else
				 {
				 	THROW_EXPECTION(NoenoughMemmoryExpection," No enough memory to new a BTreeNode...");
				 }
				 return ret;
			 }
			 SharedPointer< Tree<T> > remove( const T & value) 
			 {
				 BTreeNode<T>* node = find(value);
				 BTree<T>*ret = NULL;
				 if (node == NULL)
				 {
					 THROW_EXPECTION(InvalidParameterExpection, "can not find the value in this Btree ");
				 }
				 else
				 {
					 remove(dynamic_cast<BTreeNode<T>*>(node), ret);
					 m_queue.clear();
				 }
			 	return ret;
			 }
			 SharedPointer< Tree<T> >remove(TreeNode<T> *node)
			 {
				 BTree<T> * ret = NULL;

				 node = find(node);
				 if (node == NULL)
				 {
					 THROW_EXPECTION(InvalidParameterExpection, "node is not in this Btree ");
				 }
				 else
				 {
					 remove(dynamic_cast<BTreeNode<T>*>(node), ret);
					 m_queue.clear();
				 }
			 	return ret;
			 	
			 }
			 BTreeNode<T> * find(const T&value) const 
			 {
			 	return find(root(),value);
			 	
			 }
			 BTreeNode<T> * find(TreeNode<T> *node) const 
			 {
			 	return find( root(),dynamic_cast<BTreeNode<T>*>(node));
			 	
			 }
			 BTreeNode<T> * root() const 
			 {
			 	return dynamic_cast<BTreeNode<T>*> (this->m_root); 
			 }
			 int degree() const 
			 {
			 	return degree(root());
			 }
			 int height() const
			 {
			 	return height(root());
			 }
			 int count() const 
			 {
			 	return count(root());
			 }
	     	 void clear() 
	     	 {
				free(root());
				m_queue.clear();
	     	 	this->m_root = NULL;
			}
			 bool begin()
			 {
				 bool ret = (root() != NULL);
				 if (ret)
				 {
					 m_queue.clear();
					 m_queue.add( root());   //将根节点压入队列中 
				 }
				 return ret;
			 }
			 bool end()
			 {
				 bool  ret = (m_queue.length() == 0);
				 return ret;
			 }
			 bool next()
			 {
				 bool ret = (m_queue.length() > 0);
				 if (ret)
				 {
					 BTreeNode<T>* node = m_queue.front();
					 m_queue.remove();
					 if (node->left != NULL)
					 {
						 m_queue.add(node->left);
					 }
					 if (node->right != NULL)
					 {
						 m_queue.add(node->right);
					 }
				 }
				 return ret;
			 }
			 T current()
			 {
				 if (!end())
				 {
					 return m_queue.front()->value;   //返回队头元素所指的元素值 
				 }
				 else
				 {
					 THROW_EXPECTION(InvalidParameterExpection, "Operation is invalid...");
				 }
			 }
			 SharedPointer< Array<T> > Traversal(BTTraversal order)
			 {
				 DynamicArray<T>* ret = NULL;
				 LinkQueue<BTreeNode<T>*> queue;

				 //traversal(order, queue);
				 switch (order)
				 {
				 case PreOrder:
					 PreOrderTraversal(root(), queue);
					 break;
				 case InOrder:
					 InOrderTraversal(root(), queue);
					 break;
				 case PostOrder:
					 PostOrderTraversal(root(), queue);
					 break;
				 case LevelOrder:
					 LevelOrderTraversal(root(), queue);
					 break;
				 default:
					 THROW_EXPECTION(InvalidParameterExpection, "paramtor order is invalid...");
					 break;
				 }
				 int len = queue.length();
				 ret = new DynamicArray<T>(len);
				 if (ret != NULL)
				 {
					 for (int i = 0; i < ret->length(); i++, queue.remove())
					 {
						 ret->set(i, queue.front()->value);  //将队列里的元素值放入数组中
					 }
				 }
				 else
				 {
					 THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new ret...");
				 }
				 return ret;
			 }
			 SharedPointer< BTree<T> > clone() const
			 {
				BTree<T> * ret = new BTree();
				 if (ret != NULL)
				 {
					 ret->m_root = clone(root());
				 }
				 else
				 {
					 THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new clone ret...");
				 }
				 return ret;
			 }
			 bool operator == (const BTree<T> & tree)
			 {
				 return equal(root(), tree.root());
			 }
			 bool operator != (const BTree<T> & tree)
			 {
				 return !(*this == tree);
			 }
			 SharedPointer<BTree<T>> add(const BTree<T> &btree) const
			 {
				 BTree<T>* ret = new BTree<T>();
				 if (ret != NULL)
				 {
					 ret->m_root = add(root(), btree.root());
				 }
				 else
				 {
					 THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new add ret...");
				 }
				 return ret;
			 }
			 BTreeNode<T> *thread(BTTraversal order)   //将一颗二叉树线索化
			 {
				 BTreeNode<T> *ret = NULL;

				 LinkQueue<BTreeNode<T>*> queue;

				//traversal(order, queue);
				 switch (order)
				 {
				 case PreOrder:
					 PreOrderTraversal(root(), queue);
					 break;
				 case InOrder:
					 InOrderTraversal(root(), queue);
					 break;
				 case PostOrder:
					 PostOrderTraversal(root(), queue);
					 break;
				 case LevelOrder:
					 LevelOrderTraversal(root(), queue);
					 break;
				 default:
					 THROW_EXPECTION(InvalidParameterExpection, "paramtor order is invalid...");
					 break;
				 }
				 ret = connect(queue);

				 this->m_root = NULL;
				 queue.clear();
				 return ret;

			 }
			~BTree()
			{
				clear();
			}
		
	}; 
}

#endif //BTREE_H
