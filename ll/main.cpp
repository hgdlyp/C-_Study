#include <iostream>
#include "expection.h"
#include "SharedPointer.h"
#include"MatrixGraph.h"
#include"ListGraph.h"
#include "LinkQueue.h"
#include "Dynamicarray.h"
#include "Array.h"
#include "CircleList.h"
#include "StaticLinklist.h"
using namespace std;
using namespace DTLib;
int search_max_path(Graph<int, int > &g, int v, Array<int>&count, Array<Linklist<int>*>&path, Array<bool>&mark)  //����v�ľֲ���ඥ�����
{
	int ret = 0;
	int k = -1;
	SharedPointer<Array<int>> aj = g.getAdjacent(v); //��øö���������ڽӶ���
	for (int i = 0; i < aj->length(); i++)
	{
		int num = 0;          //����ֲ�������¼��ǰ�ڽӶ���·������������ඨ����
		if (!mark[(*aj)[i]])  //��ǰ����û�б����ʹ�
		{
			num = search_max_path(g, (*aj)[i], count, path, mark);  //��ǰ����û�б����ʹ����Ե�ǰ����Ϊ�ڵ�
		}
		else
		{
			num = count[(*aj)[i]];
		}
		if (ret < num)
		{
			ret = num;
		}
	}
	for (int i = 0; i < aj->length(); i++)
	{
		if (ret == count[(*aj)[i]])
		{
			path[v]->insert((*aj)[i]);
		}
	}
	ret++;
	count[v] = ret;
	mark[v] = true;
	return ret;
}
SharedPointer<Graph<int, int>>creat_praph(int *a, int len)
{
	ListGraph<int, int>*ret = new ListGraph<int, int>(len);
	for (int i = 0; i < len; i++)
	{
		ret->setVertex(i, a[i]);
	}
	for (int i = 0; i < len; i++)
	{
		for (int j = i+1; j < len; j++)
		{
			if (a[i] <= a[j])
			{
				ret->setEdge(i, j, 1);
			}
		}
	}
	return ret;
}
void init_array(Array<int>&count, Array<Linklist<int>*>&path, Array<bool>&mark)
{
	for (int i = 0; i < count.length(); i++)
	{
		count[i]=0;
	}
	for (int i = 0; i < path.length(); i++)
	{
		path[i] = new Linklist <int>();  //�����ڴ�ռ�ͻ��ʼ��
 	}
	for (int i = 0; i < mark.length(); i++)
	{
		mark[i] = false;
	}
}
void print_path(Graph<int, int>&g, int v, Array<Linklist<int>*>&path, Linklist<int>&cp)
{
	cp.insert(v);
	if (path[v]->length() > 0)
	{
		for (path[v]->move(0); !path[v]->end(); path[v]->next())
		{
			print_path(g, path[v]->current(), path, cp);
		}
	}
	else
	{
		cout << "Element :";
		for (cp.move(0); !cp.end(); cp.next())
		{
			cout << g.getVertex(cp.current()) << " ";
		}
		cout << endl;
	}
	cp.remove(cp.length() - 1);
}
void print_max_path(Graph<int, int>&g, Array<int>&count, Array<Linklist<int>*>&path)
{
	int max = 0;
	Linklist<int> cp;
	for (int i = 0; i < count.length(); i++)
	{
		if (max < count[i])
		{
			max = count[i];  //�ҳ��·��
		}
	}
	cout << "Len:" << max << endl;
	for (int i = 0; i < count.length(); i++)
	{
		if (max == count[i])
		{
			print_path(g, i, path, cp);
		}
	}
}
void search_max_path(Graph<int, int>&g, Array<int>&count, Array<Linklist<int>*>&path, Array<bool>&mark)
{
	for (int i = 0; i < g.vCount(); i++)
	{
		if (!mark[i])
		{
			search_max_path(g,i,count, path, mark);
		}
	}
	
}
void solution(int *a, int len)
{
	DynamicArray<int> count(len);
	DynamicArray<Linklist<int>*> path(len);
	DynamicArray<bool> mark(len);
	SharedPointer<Graph<int, int>> g;

	g = creat_praph(a, len);
	init_array(count, path, mark);
	search_max_path(*g, count, path, mark);
	print_max_path(*g, count, path);

}
int main()
{
	int a[] = { 5,4,3,2,1 };
	solution(a,sizeof(a)/sizeof(*a));
	StaticLinklist<int, 3> sl;
	for (int i = 0; i < 3; i++)
	{
		sl.insert(i);
	}
	for (int i = 0; i < 3; i++)
	{
		cout << sl.get(i) << endl;
	}
	system("pause");
	return 0;
}