#ifndef GRAPH_H
#define GRAPH_H
#include "Object.h"
#include "SharedPointer.h"
#include"Array.h"
#include "Dynamicarray.h"
#include "expection.h"
#include "LinkQueue.h"
#include "LinkStack.h"
#include "Sort.h"
using namespace std;
namespace DTLib
{
	template<typename E>
	struct Edge:public Object
	{
		int b;
		int e;
		E data;
		Edge(int i = -1, int j = -1)
		{
			b = i;
			e = j;
		}
		Edge(int i, int j, const E&value)
		{
			b = i;
			e = j;
			data = value;
		}
		bool operator == (const Edge<E> &obj)
		{
			return ((b==obj.b) && (e==obj.e));
		}
		bool operator !=(const Edge<E> &obj)
		{
			return !(*this == obj);
		}
		bool operator > (const Edge<E> &obj)
		{
			return (data > obj.data);
		}
		bool operator < (const Edge<E> &obj)
		{
			return (data < obj.data);
		}
	};

	template <typename V,typename E>
	class Graph :public Object{
	protected:
		template < typename T >
		DynamicArray<T>* Toarray( LinkQueue<T> &queue)
		{
			DynamicArray<T>*ret = new DynamicArray<T>( queue.length());
			if ( ret != NULL)
			{
				for (int i = 0; i <ret->length(); i++)  //ԭ��д����i<queue.length(),�ǲ��Ե�
				{
					ret->set(i, queue.front());
					queue.remove();
				}
			}
			else
			{
				THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new a dynamic...");
			}
			return ret;
		}
		SharedPointer<Array<Edge<E>>> getUndirectedEdges()
		{
			DynamicArray<Edge<E>> *ret = NULL;

			if (asUndirected())
			{
				LinkQueue<Edge<E>> queue;
				for (int i = 0; i < vCount(); i++)
				{
					for (int j = 0; j < vCount(); j++)
					{
						if (isAdjacent(i, j))
						{
							queue.add(Edge<E>(i, j, getEdge(i, j)));
						}
					}
				}
				ret = Toarray(queue);
				return ret;
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection," This tree can not be as a undirected tree...");
			}
		}
		int find(Array<int> &p, int v)
		{
			while (p[v] != -1)
			{
				v = p[v];
			}
			return v;
		}
	public:
		virtual V getVertex(int i) = 0;
		virtual bool getVertex(int i, V &value) = 0;
		virtual bool setVertex(int i, const V &value) = 0;
		virtual SharedPointer<Array<int>>getAdjacent(int i) = 0;
		virtual bool isAdjacent(int i, int j) = 0;
		virtual E getEdge(int i, int j) = 0;
		virtual bool getEdge(int i, int j, E&value) = 0;
		virtual bool setEdge(int i, int j,const E&value) = 0;
		virtual bool removeEdge(int i, int j) = 0;
		virtual int vCount() = 0;
		virtual int eCount() = 0;
		virtual int OD(int i) = 0;
		virtual int ID(int i) = 0;
		virtual int TD(int i)
		{
			return OD(i) + ID(i);
		}

		bool asUndirected()
		{
			bool ret = true;
			for (int i = 0; i < vCount(); i++)
			{
				for (int j = i+1; j < vCount(); j++)
				{
					if (isAdjacent(i, j))
					{
						ret = ret && (isAdjacent(j, i)) && (getEdge(i, j) == getEdge(j, i));
					}
				}
			}
			return ret;
		}

		SharedPointer<Array<Edge<E>>>prim(const E&LIMIT,const bool MINTREE = true)  //����ָ��ߵ�ָ��
		{
			LinkQueue<Edge<E>> ret;
			if (asUndirected())
			{
				DynamicArray<int> adjVex(vCount());   //����ڽӶ���
				DynamicArray<bool> mark(vCount());  //��Ƕ��������ĸ�������
				DynamicArray<E> cost(vCount());    //���Ȩֵ
				SharedPointer<Array<int>> aj = NULL;
				bool end = false;
				int v = 0;

				for (int i = 0; i < vCount(); i++)
				{
					adjVex[i] = -1;
					mark[i] = false;
					cost[i] = LIMIT;
				}
				mark[v] = true;
				aj = getAdjacent(v);    //�õ���v���ڵĶ���ֵ
				for (int j = 0; j < aj->length(); j++)
				{
					cost[(*aj)[j]] = getEdge(v, (*aj)[j]);  //cost����ߵ�Ȩֵ ��v ���ٽֶ����Ȩֵ���浽cost ������
					adjVex[(*aj)[j]] = v; //���߱�������
				}
				for (int i = 0; i < vCount(); i++)  //����ѭ������Ϊÿ�δ�F�������ó�һ��Ԫ�ص�T�����У�����Ҫѭ�� vCount()��
				{
					E m = LIMIT;
					int k = -1;

					for (int j = 0; j < vCount(); j++)
					{
						if (!mark[j] && (MINTREE ? (cost[j] < m) : (cost[j] > m)))
						{
							m = cost[j];
							k = j;   // k���ǽ�����Ҫ����T�����еĶ���
						}
					}
					end = (k == -1);   //���k����-1 ˵������k�����ʵ�λ�ò��Ϸ�
					if (!end)
					{
						ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));   //��Ȩֵ��С�ı߼��뵽ret��
						mark[k] = true;
						aj = getAdjacent(k);
						for (int j = 0; j < aj->length(); j++)
						{
							if ( !mark[(*aj)[j]] && ( MINTREE ? getEdge(k, (*aj)[j]) <cost[(*aj)[j]] : getEdge(k,(*aj)[j]) > cost[(*aj)[j]]))
							{
								cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
								adjVex[(*aj)[j]] = k;
							}
						}
					}
				}

			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the tree can not conservet a undirected tree ...");
			}
			if (ret.length() != vCount() - 1)
			{
				THROW_EXPECTION(InvalidParameterExpection, "the edges is not enough ...");
			}
			return Toarray(ret);
		}
		SharedPointer<Array<Edge<E>>> kruskal(bool MINTREE = true)  //Ĭ��������С��������Ϊfalseʱ���������
		{
			LinkQueue<Edge<E>> ret;
			SharedPointer<Array<Edge<E>>> edges = getUndirectedEdges();
			DynamicArray<int> p(vCount());
			for (int i = 0; i < vCount(); i++)
			{
				p[i] = -1;
			}
			Sort::Hill(*edges,MINTREE);
			for (int i = 0; (i < edges->length()) && ret.length() < (vCount() - 1); i++)
			{
				int b = find(p, (*edges)[i].b);  //��¼�ߵ���ʼ��
				int e = find(p, (*edges)[i].e);  //��¼�ߵĽ�����
				if (b!= e)
				{
					p[e] = b;
					ret.add((*edges)[i]);
				}
			}
			if (ret.length() != (vCount() - 1))
			{
				THROW_EXPECTION(InvalidParameterExpection, "there is no enough edges to create a min tree...");
			}
			return Toarray(ret);
		}

		SharedPointer<Array<int>> BFS(int i)
		{
			DynamicArray<int> * ret = NULL;  //����ֵΪ�������ڴ洢��������ͼ�ڵ��˳��

			if ((0 <= i) && (i < vCount()))
			{
				LinkQueue<int> q;
				LinkQueue<int> r;
				DynamicArray<bool> visited(vCount());//������ǵ�ǰ�ڵ��Ƿ񱻷��ʹ�

				for (int j = 0; j < visited.length(); j++)
				{
					visited[j] = false;
				}

				q.add(i);

				while ( q.length()>0 )
				{
					int v = q.front();

					q.remove();

 					if (!visited[v])   //û�б����ʹ��Ľڵ�
					{
						SharedPointer<Array<int>> aj = getAdjacent(v);  //v�ڵ�������ڽӶ���

						for (int j = 0;j <aj->length(); j++)
						{
							q.add((*aj)[j]);
						}

						r.add(v);  //�����еĳ��Ⱦ�Ȼֻ��4 ��
						visited[v] = true;
					}
				}
				ret = Toarray(r);
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection,"the parameter i is invalid");
			}
			return ret;
		}
		SharedPointer<Array<int>> DFS(int i)
		{
			DynamicArray<int> * ret = NULL;  //����ֵΪ�������ڴ洢��������ͼ�ڵ��˳��
			if ((0 <= i) && (i < vCount()))
			{
				LinkQueue<int> r;
				LinkStack<int> s;
				DynamicArray<bool> visited(vCount());

				for (int j = 0; j < visited.length(); j++)
				{
					visited[j] = false;
				}
				s.push(i);  //��iѹ��ջ��

				while (s.size()>0)
				{
					int v = s.top();
					s.pop();
					if (!visited[v])
					{
						SharedPointer<Array<int>> aj = getAdjacent(v);  //v�ڵ�������ڽӶ���

						for (int j=aj->length()-1; j>=0; j--)
						{
							s.push((*aj)[j]);
						}
						r.add(v);
						visited[v] = true;
					}
				}
				
				ret = Toarray(r);
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid");
			}
			return ret;
		}
		template<typename V, typename E>
		void RecursionDFS(Graph<V, E> &g, int v, Array<bool> &visited)  //��ȱ����ĵݹ���ʽ
		{
			if ((0 <= v) && (v < g.vCount()))
			{
				cout << v << endl;
				visited[v] = true;

				SharedPointer< Array<int> > aj = g.getAdjacent(v);
				for (int j = 0; j < aj->length(); j++)
				{
					if (!visited[(*aj)[j]])
					{
						RecursionDFS(g, (*aj)[j], visited);
					}
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, " error...");
			}
		}

		template<typename V, typename E>
		void RecursionDFS(Graph<V, E>&g, int v)
		{
			DynamicArray<bool> visited(g.vCount());
			for (int i = 0; i < visited.length(); i++)
			{
				visited[i] = false;
			}
			RecursionDFS(g, v, visited);
		}
		SharedPointer<Array<int>>dijkstra(int i, int j,const E&LIMIT)
		{
			LinkQueue< int> ret;
			if ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
			{
				DynamicArray<E> dist(vCount());
				DynamicArray<int> path(vCount());
				DynamicArray<bool> mark(vCount());
				for (int k = 0; k < vCount(); k++)
				{
					mark[k] = false;
					path[k] = -1;
					dist[k] = isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT;  //���ǰ���ڵ㲢��ȡ�ߵ�Ȩֵ
				}
				mark[i] = true;
				for (int k = 0; k < vCount(); k++)
				{
					E m = LIMIT;
					int u = 1;
					for (int w = 0; w < vCount(); w++)
					{
						if (!mark[w] && (dist[w] < m))
						{
							m = dist[w];
							u = w;
						}
					}
					if (u == -1)
					{
						break;
					}
					mark[u] = true;
					for (int w = 0; w < vCount(); w++)
					{
						if (!mark[w] && isAdjacent(u, w) && (dist[u] + getEdge(u, w) < dist[w]))
						{
							dist[w] = dist[u] + getEdge(u, w);
							path[w] = u;
						}
					}
				}
				LinkStack<int> s;
				s.push(j);
				for (int k = path[j]; k != -1; k = path[k])
				{
					s.push(k);
				}
				while (s.size() > 0)
				{
					ret.add(s.top());
					s.pop();
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "parametor i,j is invalid...");
			}
			if (ret.length() < 2)
			{
				THROW_EXPECTION(ArithmeticExpection,"There is no path from i to j...");
			}
			return Toarray(ret);
		}
		SharedPointer<Array<int>> floyd(int x, int y,const E&LIMIT)
		{
			LinkQueue<int> ret;
			if ((0<=x) && (x<vCount()) && (0<=y) && (y<vCount()))
			{
				DynamicArray<DynamicArray<E>> dist(vCount());
				DynamicArray<DynamicArray<int>> path(vCount());
				for (int k = 0; k < vCount(); k++)
				{
					path[k].resize(vCount());
					dist[k].resize(vCount());
				}
				for (int i = 0; i < vCount(); i++)
				{
					for (int j = 0; j < vCount(); j++)
					{
						path[i][j] = -1;
						dist[i][j] = isAdjacent(i, j) ? (path[i][j]=j,getEdge(i, j)) : LIMIT;
					}
				}
				for (int k = 0; k < vCount(); k++)
				{
					for (int i = 0; i < vCount(); i++)
					{
						for (int j = 0; j < vCount(); j++)
						{
							if ((dist[i][k] + dist[k][j]) < dist[i][j])
							{
								dist[i][j] = dist[i][k] + dist[k][j];
								path[i][j] = path[i][k];
							}
						}
					}
				}
				while ((x != -1) && (x != y))
				{
					ret.add(x);
					x = path[x][y];
				}
				if (x != -1)
				{
					ret.add(x);
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "parametor <x,y> is invalid...");
			}
			if (ret.length() < 2)
			{
				THROW_EXPECTION(ArithmeticExpection, "There is no path from i to j...");
			}
			return Toarray(ret);
		}
	};

}

#endif //GRAPH_H