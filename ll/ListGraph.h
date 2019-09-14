#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "expection.h"
#include "Dynamicarray.h"
#include "LinkList.h"
namespace DTLib{
	template <typename V, typename E>
	class ListGraph : public Graph<V, E>
	{
	protected:
		struct Vertex :public Object
		{
			V *data;
			Linklist<Edge<E>> edge;
			Vertex()                                                                                                                                                                                                                                                                                                                                             
			{
				data = NULL;
			}
		};
		Linklist<Vertex*> m_list;
	public:
		ListGraph(unsigned int n = 0)
		{
			for (int i = 0; i < n; i++)
			{
				addVertex();
			}
		}
		int addVertex()
		{
			int ret = -1;
			Vertex *ve = new Vertex();
			if (ve != NULL)
			{
				m_list.insert(ve);
				ret = m_list.length() - 1;  //返回值为新的顶点在链表末尾的编号
			}
			else
			{
				THROW_EXPECTION(NoenoughMemmoryExpection, " no enough memory to creat a new Vertex...");
			}
			return ret;
		}
		int addVertex(const V&value)
		{
			int ret = addVertex();
			if (ret >= 0)
			{
				setVertex(ret, value);
			}
			return ret;
		}
		bool setVertex(int i, const V&value)
		{
			bool ret = ((0 <= i) && (i < vCount()));
			if (ret)
			{
				Vertex *vertex = m_list.get(i);  //获取当前位置的顶点
				V *data = vertex->data;  //定义新的指针指向数据元素
				if (data == NULL)
				{
					data = new V();
				}
				if (data != NULL)
				{
					*data = value;
					vertex ->data= data;
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection, " no enough memory to creat a new V data...");
				}
			}
			return ret;
		}
		V getVertex(int i)
		{
			V ret = 0;
			if (!getVertex(i, ret))
			{
				THROW_EXPECTION(InvalidParameterExpection, "the paramete i is invalid...");
			}
			return ret;
		}
		bool getVertex(int i, V &value)
		{
			bool ret = ((0 <= i) && (i < vCount()));
			if (ret)
			{
				Vertex *v = m_list.get(i);
				if (v->data != NULL)
				{
					value = *(v->data);
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection, "the current vertex dont has a value...");
				}
			}
			return ret;
		}

		void removeVertex()  //比较难的一部分
		{
			if (m_list.length() > 0)
			{
				int index = m_list.length() - 1;  //只能在图临街链表的尾部进行删除元素操作

				Vertex * v = m_list.get(index);  //得到 指向最后节点的指针值
				if (m_list.remove(index))       //从邻接链表中删除最后一个节点
				{
					for (int i=(m_list.move(0),0); !m_list.end(); i++,m_list.next())  //逗号表达式结果是 i的值是最后一项的值
					{
						int pos = m_list.current()->edge.find(Edge<E>(i, index)); //寻找所有以index为结束的边；
						if (pos >= 0)     // 存在与要删除顶点的边
						{
							m_list.current()->edge.remove(pos);  //删除与之相关的边
						}
					}
					delete v->data;   //释放顶点v的数据
					delete v;        //释放顶点
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "no vertex in this m_list...");
			}
		}
		SharedPointer<Array<int>>getAdjacent(int i)
		{
			DynamicArray<int> *ret = NULL;
			if ((0 <= i) && (i < vCount()))
			{
				Vertex* vertex = m_list.get(i);
				ret = new DynamicArray<int>(vertex->edge.length());
				if (ret != NULL)
				{
					for (int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, vertex->edge.next())
					{
						ret->set(k, vertex->edge.current().e);
					}
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection, " no enough memory to creat a new ret...");
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid...");
			}
			return ret;
		}
	     bool isAdjacent(int i, int j)
		{
			 return (0 <= i) && (i < vCount()) && (j < vCount()) && (0 <= j) && (m_list.get(i)->edge.find(Edge<E>(i, j)) >= 0);
		}
		E getEdge(int i, int j)  //得到ij的值
		{
			E ret = 0;
			if (!getEdge(i, j, ret))
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i,j is invalid...");
			}
			return ret;
		}
		bool getEdge(int i, int j, E&value)
		{
			bool ret = ((0 <= i && i < vCount()) && (j< vCount() && 0 <= j));
			if (ret)
			{
				Vertex *vertex = m_list.get(i);
				int pos = vertex->edge.find(Edge<E>(i, j));   //找到ij的位置
				if (pos >= 0)   //包括0位置，不能只大于0
				{
					value = vertex->edge.get(pos).data;
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection, "the parameter i,j is invalid...");
				}
			}
			return ret;
		}
		bool setEdge(int i, int j, const E& value)
		{
			bool ret = ((0 <= i) && (i < vCount()) && (j<vCount()) && (0 <= j));
			if (ret)
			{
				Vertex * vertex = m_list.get(i);
				int pos = vertex->edge.find(Edge<E>(i,j));
				if (pos > 0)
				{
					ret = vertex->edge.set(pos, Edge<E>(i, j, value));
				}
				else
				{
					ret = vertex->edge.insert(0, Edge<E>(i, j, value));
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i,j is invalid...");
			}
		}
		bool removeEdge(int i, int j)
		{
			bool ret = ((0 <= i) && (i < vCount()) && (j<vCount()) && (0 <= j));
			if (ret)
			{
				Vertex * vertex = m_list.get(i);
				int pos = vertex->edge.find(Edge<int>(i, j));
				if (pos >= 0)
				{
					ret = vertex->edge.remove(pos);
				}
			}
			return ret;
		}
		int vCount()
		{
			return m_list.length();
		}
		int eCount()
		{
			int e_count = 0;
			for (m_list.move(0); !m_list.end(); m_list.next())
			{
				e_count += m_list.current()->edge.length();
			}
			return e_count;
		}
		int ID(int i)
		{
			int ret = 0;
			if ((0 <= i) && (i < vCount()))
			{
				for (m_list.move(0); !m_list.end(); m_list.next())
				{
					Linklist<Edge<int>> &edge = m_list.current()->edge;
					for (edge.move(0); !edge.end(); edge.next())  //遍历边的邻接链表
					{
						if (edge.current().e == i)
						{
							ret++;
							break;
						}
					}
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i,j is invalid...");
			}
			return ret;
		}
		int OD(int i)
		{
			int ret = 0;
			if ((0 <= i) && (i < vCount()))
			{
				ret = m_list.get(i)->edge.length();
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i,j is invalid...");
			}
			return ret;
		}
		~ListGraph()
		{
			while (m_list.length() > 0)
			{
				Vertex *toDel = m_list.get(0);
				m_list.remove(0);

				delete toDel->data;
				delete toDel;
			}
		}
	};
}

#endif //LISTGRAPH_H