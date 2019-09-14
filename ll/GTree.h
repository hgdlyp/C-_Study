#ifndef GTREE_H_
#define GTREE_H_
#include "Tree.h"
#include "GTreeNode.h"
#include "expection.h"
#include "LinkQueue.h"
namespace DTLib{
	template <typename T>
	class GTree : public Tree<T> {
		protected:
			LinkQueue< GTreeNode<T>* > m_queue;
			GTreeNode<T>* find( GTreeNode<T>* node, const T&value) const  //通用树中的查找操作 
			{
			   GTreeNode<T>* ret = NULL;
			   if( node !=NULL)
			   {
				   	if( node->value == value) 
					   {
					   	return node;
					   }
				   	else
				   	{
				   		for(node->child.move(0); !node->child.end() && (ret==NULL);node->child.next())
				   		{
				   			ret = find(node->child.current(),value);
						}
					}
			   }
			   return ret;
			}
			GTreeNode<T>* find( GTreeNode<T>* node, GTreeNode<T> *obj) const
			{
				 GTreeNode<T>* ret = NULL;
				 if(node == obj)
				 {
				 	return node;
				 }
				 else
				 {
				 	if( node != NULL)
				 	{
				 		for(node->child.move(0); (!node->child.end() && (ret==NULL));node->child.next()) //错误在这里感叹号写错地方 
				   		{
				   			ret = find(node->child.current(),obj);
						}
					 }
				 }
				 return ret;
			}
			void free(GTreeNode<T> * node)
			{
				if( node !=NULL)
				{
					for(node->child.move(0);!node->child.end(); node->child.next())
					{
						free(node->child.current());
					}
					if( node->flag())
					{
						delete node;
					}
				}
			 } 
			 void remove(GTreeNode<T>* node,GTree<T>* &ret)
			 {
			 	ret = new GTree<T>();
			 	if( ret == NULL)
				 {
				 	THROW_EXPECTION(NoenoughMemmoryExpection," No enough memory to new a GTree...");
				  }
				  else
				  {
				  	if( root() == node)
				  	{
				  		this->m_root =NULL;
					  }
					  else
					  {
					  	Linklist<GTreeNode<T>*> &child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
					  	child.remove(child.find(node));
					  	node->parent = NULL;
					  }
					  ret->m_root = node;
				   }   
			 } 
			 int count( GTreeNode<T>* node) const  //递归实现计数 
			 {
			 	int ret = 0;
			 	if(node !=NULL)
			 	{
			 		 ret = 1;
					 for(node->child.move(0); !node->child.end();node->child.next()) 
					 {
					 	ret+=count(node->child.current());
					 }
				 } 
			 	return ret;
			 }
			 int height(GTreeNode<T> * node) const
			 {
			 	int ret = 0;
			 	if(node!=NULL)
			 	{
			 		ret = 1;
			 		for(node->child.move(0); !node->child.end();node->child.next()) 
			 		{
			 			int h = height (node->child.current()) ;
			 			if( ret < h)
						{
							ret = h;
						}	
					} 
					
				 }
			 	return ret+1;
			  } 
			  int degree(GTreeNode<T>*node) const
			  {
			  	int ret = 0;
			  	if( node!=NULL )
			  	{
			  		ret = node->child.length();
			  		for(node->child.move(0); !node->child.end();node->child.next()) 
			 		{
			 			 int d = degree(node->child.current()) ;
				 		if(ret < d)
				 		{
				 		   ret = d;
						}
			 		}
			 		
				}
				return ret;
			  }
		public:
			GTree()
			{
				
			 } 
		bool insert(TreeNode<T> *node)
		{
			bool ret = true; 
			if( node != NULL)
			{
				if( this->m_root == NULL)
				{
					node->parent = NULL;
					this->m_root = node;
				}
				else
				{
					GTreeNode<T> *np = find(node->parent);  //找到该节点的父节点 
					if( np != NULL)
					{
						GTreeNode<T> *n = dynamic_cast<GTreeNode<T>*>(node);
						if( np->child.find(n)<0 )
						{
						 	np->child.insert(n);
						}
					}
					else
					{
						THROW_EXPECTION(InvalidParameterExpection,"Parent node is NULL...");
					}
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection,"to insert node cannot be NULL...");
			} 
			return ret;
		}
		bool insert(const T& value,TreeNode<T> *parent)
		{
		    bool ret = true; 
		    GTreeNode<T> *node = GTreeNode<T>::NewNode();
		    if( node != NULL)
		    {
		    	node->value = value;
		    	node->parent = parent;
		        insert(node);
			}
		  else
		  {
		  	THROW_EXPECTION(NoenoughMemmoryExpection," No enough memory to new a GTreeNode...");
		  }
			return ret;
		}
	    SharedPointer< Tree<T> > remove( const T & value)
	    {
	    	GTree<T> * ret = NULL;
	    	GTreeNode<T> *node = find(value);
	    	if(node == NULL)
	    	{
	    		THROW_EXPECTION(InvalidParameterExpection,"value is invalid...");
			}
			else
			{
				remove(node,ret);
				m_queue.clear();
			}
	     	return ret;
	    }
		SharedPointer< Tree<T> > remove(TreeNode<T> *node)
		{
			GTree<T> * ret = NULL;
	    	node = find(node);
	    	if(node == NULL)
	    	{
	    		THROW_EXPECTION(InvalidParameterExpection,"value is invalid...");
			}
			else
			{
				remove(dynamic_cast<GTreeNode<T>*>(node), ret);
				m_queue.clear();
			}
	     	return ret;
		}
		GTreeNode<T> * find(const T&value) const
		{
			return find(root(),value);
		}
		GTreeNode<T> * find(TreeNode<T> *node) const 
		{
			return find(root(),dynamic_cast<GTreeNode<T>*>(node));
		}
		GTreeNode<T> * root() const
		{
			return dynamic_cast<GTreeNode<T>*> (this->m_root);
		}
		int degree() const 
		{
			return degree(root());
		}
		int height() const
		{
			return height(root());
		}
		int count() const    //数的节点数 
		{
			return count(root());
		}
		bool begin()
		{
			bool ret =( root()!=NULL);
			if(ret)
			{
				m_queue.clear();
				m_queue.add(root());   //将根节点压入队列中 
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
			if(ret)
			{
				GTreeNode<T>* node = m_queue.front();
				m_queue.remove();
				for(node->child.move(0);!node->child.end();node->child.next())
				{
					m_queue.add(node->child.current());
				}
			}
			return ret;
		}
		T current()
		{
			if(!end())
			{
				return m_queue.front()->value;   //返回队头元素所指的元素值 
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection,"Operation is invalid...");
			}
		}
		void clear() 
		{
			free(root());
			this->m_root = NULL;
			m_queue.clear();
		}
		~GTree()
		{
			clear();
		}
	};
}

#endif //GTREE_H_
