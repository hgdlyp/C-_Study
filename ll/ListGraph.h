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
				ret = m_list.length() - 1;  //����ֵΪ�µĶ���������ĩβ�ı��
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
				Vertex *vertex = m_list.get(i);  //��ȡ��ǰλ�õĶ���
				V *data = vertex->data;  //�����µ�ָ��ָ������Ԫ��
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

		void removeVertex()  //�Ƚ��ѵ�һ����
		{
			if (m_list.length() > 0)
			{
				int index = m_list.length() - 1;  //ֻ����ͼ�ٽ������β������ɾ��Ԫ�ز���

				Vertex * v = m_list.get(index);  //�õ� ָ�����ڵ��ָ��ֵ
				if (m_list.remove(index))       //���ڽ�������ɾ�����һ���ڵ�
				{
					for (int i=(m_list.move(0),0); !m_list.end(); i++,m_list.next())  //���ű��ʽ����� i��ֵ�����һ���ֵ
					{
						int pos = m_list.current()->edge.find(Edge<E>(i, index)); //Ѱ��������indexΪ�����ıߣ�
						if (pos >= 0)     // ������Ҫɾ������ı�
						{
							m_list.current()->edge.remove(pos);  //ɾ����֮��صı�
						}
					}
					delete v->data;   //�ͷŶ���v������
					delete v;        //�ͷŶ���
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
		E getEdge(int i, int j)  //�õ�ij��ֵ
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
				int pos = vertex->edge.find(Edge<E>(i, j));   //�ҵ�ij��λ��
				if (pos >= 0)   //����0λ�ã�����ֻ����0
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
					for (edge.move(0); !edge.end(); edge.next())  //�����ߵ��ڽ�����
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