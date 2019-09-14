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
				for (int i = 0; i <ret->length(); i++)  //原来写的是i<queue.length(),是不对的
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

		SharedPointer<Array<Edge<E>>>prim(const E&LIMIT,const bool MINTREE = true)  //返回指向边的指针
		{
			LinkQueue<Edge<E>> ret;
			if (asUndirected())
			{
				DynamicArray<int> adjVex(vCount());   //标记邻接顶点
				DynamicArray<bool> mark(vCount());  //标记顶点是在哪个集合中
				DynamicArray<E> cost(vCount());    //标记权值
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
				aj = getAdjacent(v);    //得到与v相邻的顶点值
				for (int j = 0; j < aj->length(); j++)
				{
					cost[(*aj)[j]] = getEdge(v, (*aj)[j]);  //cost保存边的权值 将v 的临街顶点的权值保存到cost 数组中
					adjVex[(*aj)[j]] = v; //将边保存下来
				}
				for (int i = 0; i < vCount(); i++)  //进行循环，因为每次从F集合中拿出一个元素到T集合中，所以要循环 vCount()次
				{
					E m = LIMIT;
					int k = -1;

					for (int j = 0; j < vCount(); j++)
					{
						if (!mark[j] && (MINTREE ? (cost[j] < m) : (cost[j] > m)))
						{
							m = cost[j];
							k = j;   // k点是接下来要放入T集合中的顶点
						}
					}
					end = (k == -1);   //如果k等于-1 说明出错，k待访问的位置不合法
					if (!end)
					{
						ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));   //将权值最小的边加入到ret中
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
		SharedPointer<Array<Edge<E>>> kruskal(bool MINTREE = true)  //默认生成最小生成树，为false时最大生成树
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
				int b = find(p, (*edges)[i].b);  //记录边的起始点
				int e = find(p, (*edges)[i].e);  //记录边的结束点
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
			DynamicArray<int> * ret = NULL;  //返回值为数组用于存储遍历访问图节点的顺序

			if ((0 <= i) && (i < vCount()))
			{
				LinkQueue<int> q;
				LinkQueue<int> r;
				DynamicArray<bool> visited(vCount());//用来标记当前节点是否被访问过

				for (int j = 0; j < visited.length(); j++)
				{
					visited[j] = false;
				}

				q.add(i);

				while ( q.length()>0 )
				{
					int v = q.front();

					q.remove();

 					if (!visited[v])   //没有被访问过的节点
					{
						SharedPointer<Array<int>> aj = getAdjacent(v);  //v节点的所有邻接顶点

						for (int j = 0;j <aj->length(); j++)
						{
							q.add((*aj)[j]);
						}

						r.add(v);  //最后队列的长度竟然只有4 。
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
			DynamicArray<int> * ret = NULL;  //返回值为数组用于存储遍历访问图节点的顺序
			if ((0 <= i) && (i < vCount()))
			{
				LinkQueue<int> r;
				LinkStack<int> s;
				DynamicArray<bool> visited(vCount());

				for (int j = 0; j < visited.length(); j++)
				{
					visited[j] = false;
				}
				s.push(i);  //将i压入栈中

				while (s.size()>0)
				{
					int v = s.top();
					s.pop();
					if (!visited[v])
					{
						SharedPointer<Array<int>> aj = getAdjacent(v);  //v节点的所有邻接顶点

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
		void RecursionDFS(Graph<V, E> &g, int v, Array<bool> &visited)  //深度遍历的递归形式
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
					dist[k] = isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT;  //标记前驱节点并获取边的权值
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