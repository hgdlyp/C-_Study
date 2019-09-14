#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H
#include "Graph.h"
#include "expection.h"
#include "Dynamicarray.h"
namespace DTLib
{
	template < int N, typename V, typename E >
	class MatrixGraph : public Graph<V, E>
	{
	protected:
		V* m_vertexes[N];
		E* m_edges[N][N];
		int m_ecount;
	public:
		MatrixGraph()
		{
			for (int i = 0; i < N; i++)
			{
				m_vertexes[i] = NULL;
				for (int j = 0; j < N; j++)
				{
					m_edges[i][j] = NULL;
				}
			}
			m_ecount = 0;
		}

		 V getVertex(int i)
		{
			V ret;
			if (!getVertex(i, ret));
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid...");
			}
			return ret;
		}
		 bool getVertex(int i, V &value)
		{
			bool ret = ((0 <= i) && (i < vCount()));
			if (ret)
			{
				if ( m_vertexes[i] != NULL)
				{
					value = *(m_vertexes[i]);
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid...");
				}
			}
			return ret;
		}
		bool setVertex(int i, const V &value)
		{ 
			bool ret = ((0 <= i) && (i < vCount()));
			if (ret)
			{
				V* data = m_vertexes[i];
				if (data == NULL)
				{
					data = new V();
				}
				if (data != NULL)
				{
					*data = value;
					m_vertexes[i] = data;
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to dtore a new value");
				}
			}
			return ret;
		}
		SharedPointer<Array<int>>getAdjacent(int i)
		{
			DynamicArray<int> * ret = NULL;
			if ((0 <= i) && (i < vCount()))
			{
				int  n = 0; //用来记录与i邻接元素的个数
				for (int j = 0; j < vCount(); j++)
				{
					if (m_edges[i][j] != NULL)
					{
						n++;
					}
				}
				ret = new DynamicArray<int>(n);
				if (ret != NULL)
				{
					for (int j = 0, k = 0; j < vCount(); j++)
					{
						if (m_edges[i][j] != NULL)
						{
							ret->set(k++, j);   //将与i点对应的临街节点放到数组中
						}
						
					}
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new ret value");
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
			return (0 <= i) && (i < vCount()) && (j < vCount()) && (0 <= j) && (m_edges[i][j] != NULL);
		}
		E getEdge(int i, int j)  //得到ij的值
		{
			E ret = 0;
			if (!getEdge(i, j,ret))
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i,j is invalid...");
			}
			return ret;
		}
		bool getEdge(int i, int j, E&value)
		{
			bool ret = ((0 <= i) && (i < vCount()) &&(j<vCount())&&(0<=j));
			if (ret)
			{
				if (m_edges[i][j] != NULL)
				{
					value = *(m_edges[i][j]);
				}
				else
				{
					THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid...");
				}
			}
		}
		bool setEdge(int i, int j, const E&value)
		{
			bool ret = ((0 <= i) && (i < vCount()) && (j<vCount()) && (0 <= j));
			if (ret)
			{
				E *ne = m_edges[i][j];
				if (ne==NULL)
				{
					ne = new E();
					if (ne != NULL)
					{
						*ne = value;
						m_edges[i][j] = ne;
						m_ecount++;
					}
					else
					{
						THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new ne value");
					}

				}
				else
				{
					 *ne = value;  //在这里ne 指向它所指的空间。
				}
			}
			return ret;
		}
		bool removeEdge(int i, int j)
		{
			bool ret = ((0 <= i) && (i < vCount()) && (j<vCount()) && (0 <= j));
			if (ret)
			{
				E *toDel = m_edges[i][j];
				m_edges[i][j] = NULL;
				if (toDel != NULL)
				{
					m_ecount--;
					delete toDel;
				}
				else
				{
					THROW_EXPECTION(NoenoughMemmoryExpection, "no enough memory to new ne value");
				}
			}
			return ret;
		}
		int vCount()
		{
			return N;
 		}
	    int eCount()
		{
			return m_ecount;
		}
		int OD(int i)
		{
			int ret = 0;
			if ((0 <= i) && (i < vCount()))
			{
				for (int j = 0; j < vCount(); j++)
				{
					if (m_edges[i][j] != NULL)  //i点所在这一行，所有不为0的个数就是该图的出度；
					{
						ret++;
					}
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid...");
			}
			return ret;
		}
		int ID(int i)
		{
			int ret = 0;
			if ((0 <= i) && (i < vCount()))
			{
				for (int j = 0; j < vCount(); j++)
				{
					if (m_edges[j][i] != NULL) // //i点所在这一列，所有不为0的个数就是该图的出度；
					{
						ret++;
					}
				}
			}
			else
			{
				THROW_EXPECTION(InvalidParameterExpection, "the parameter i is invalid...");
			}
			return ret;
		}

		~MatrixGraph()
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					delete m_edges[i][j];
				}
				delete m_vertexes[i];
			}
		}
	};
}

#endif //MATRIXGRAPH_H