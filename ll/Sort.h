#ifndef SORT_H_
#define SORT_H_

#include"Object.h"
#include "Array.h" 
namespace DTLib{
	class Sort : public Object{
		protected:
			Sort();
			Sort( const Sort &);
			Sort &operator = (const Sort &);
			template <typename T>
			static void Swap( T&a,T&b)
			{
				T c(a);
				a = b;
				b = c;
			
			}
		template<typename T>
		static void Merge(T src[],T helper[],int begin,int mid,int end,bool min2max )
		{
			int i = begin;
			int j = mid+1;  //后半部分的起始位置 
			int k = begin;   // 辅助空间的起始位置 
			while((i <= mid) && (j<=end))
			{
				if( min2max?(src[i] < src[j]):(src[i] > src[j]))
				{
					helper[k++] = src[i++];
				}
				else
				{
					helper[k++] = src[j++];
				}
			} 
			while(i<=mid)
			{
				helper[k++] = src[i++];
			}
			while(j<=end)
			{
				helper[k++] = src[j++];
			}
			for (int i= begin;i<=end;i++)
			{
				src[i] = helper[i];
			}
		}
		template<typename T>
		static void Merge(T array[],T helper[],int begin,int end,bool min2max )
		{
			if( begin < end )
			{
				 int mid = (begin + end) /2;
				
				 Merge(array,helper,begin,mid,min2max);
				 Merge(array,helper,mid+1,end,min2max);
				 Merge(array,helper,begin,mid,end,min2max);
			}
		}
		template<typename T>
		static int Parttion( T array[],int begin,int end,bool min2max)
		{
			int pv = array[begin];
			while( begin < end)    //当begin == end时结束循环
			{
				while( (begin < end) && (min2max?(array[end] > pv) :(array[end] < pv))) 
				{
					end --;
				}
				Swap(array[begin],array[end]);
				while( ( begin< end) && min2max?(array[begin] <pv) :(array[begin] > pv))
				{
					begin ++ ;
				}
				Swap( array[begin],array[end]);
			} 
			array[begin] = pv;
			return begin;
		}
		template<typename T>
		static void Quick( T array[],int begin,int end,bool min2max)
		{
			int pivor = Parttion( array,begin,end,min2max);
			if(begin<end)
			{
				Quick(array,begin,pivor-1,min2max);
				Quick(array,pivor+1,end,min2max);
			}	
		}
		public:
			template<typename T>
		static void Select( T array[],int len,bool min2max = true)
		{
			for(int i =0;i<len;i++)
			{
				int min = i;
				for(int j = i+1;j<len;j++)
				{
					if( min2max ? (array[min] > array[j]) : (array[min] < array[j]))
					{
						min = j;
					}
				}
				if( min != i)
				Swap(array[min],array[i]);
			}
		}
		template<typename T>
		static void Insert( T array[],int len,bool min2max = true)	
		{
			for( int i = 1;i<len;i++)
			{
				int k =i;
				T e = array[i];
				for(int j=i-1;( j>=0)&& (min2max? (array[j] > e) :(array[j] < e));j--)
				{
					array[j+1] = array[j];
					k = j;
				}
				if(k!=i)
				{
					array[k] = e;
				}
			}
		}	
	template<typename T>
		static void Bubble( T array[],int len,bool min2max = true)    //O(n^2)
		{
			bool exchange = true;   //定义是否进行交换操作的标志位
			
			for(int i = 0; (i<len)&&exchange;i++)
			{
				exchange = false;
				for( int j =len-1;j>i;j--)
				{
					if( min2max?(array[j]<array[j-1]):(array[j]>array[j-1]) )
					{
						Swap(array[j],array[j-1]);
						exchange = true;
					}	
				}	
			} 
		}
	template<typename T>
		static void Hill( T array[],int len,bool min2max = true)   //O(n^3/2)
		{
			int d = len;
			do{
				d = d/3+1;
				for( int i =d;i<len;i+=d)
				{
					int k =i;
					T e = array[i];
					for(int j=i-d;( j>=0)&& (min2max? (array[j] > e) :(array[j] < e));j-=d)
					{
						array[j+d] = array[j];
						k = j;
					}
					if(k!=i)
					{
						array[k] = e;
					}
				}
		}while(d>1);
	}
	    template<typename T>
		static void Merge( T array[],int len,bool min2max = true)   
		{
			T *helper = new T[len];
			if( helper !=NULL )
			{
				Merge(array,helper,0,len-1,min2max);
			}
		}
		template<typename T>
		static void Quick( T array[],int len,bool min2max = true)   
		{
			Quick(array,0,len-1,min2max);
		}
		template<typename T>
		static void Select(Array<T> &array,bool min2max = true)
		{
			Select(array.array(),array.length(),min2max);
		}
		template<typename T>
		static void Insert(Array<T> &array,bool min2max = true)
		{
			Insert(array.array(),array.length(),min2max);
		}
		template<typename T>
		static void Bubble(Array<T> &array,bool min2max = true)
		{
			Bubble(array.array(),array.length(),min2max);
		}
		template<typename T>
		static void Hill(Array<T> &array,bool min2max = true)
		{
			Hill(array.array(),array.length(),min2max);
		}
		template<typename T>
		static void Merge(Array<T> &array,bool min2max = true)
		{
			Merge(array.array(),array.length(),min2max);
		}
		template<typename T>
		static void Quick(Array<T> &array,bool min2max = true)
		{
			Quick(array.array(),array.length(),min2max);
		}
	};
}

#endif //SORT_H_ 
