#ifndef ARRAY__HH__
#define ARRAY__HH__
#include "Object.h"
#include "expection.h"
namespace DTLib{
	template <typename T>
	class Array : public Object{
		protected:
			T *m_array;
		public:
			virtual bool set(int i,const T&e)
			{
					bool ret = ((0<=i) && (i<length()));
					if(ret)
					{
						m_array[i] = e;
					}
					return ret;
			} 
			virtual bool get(int i, T&e) const
			{
					bool ret = ((0<=i) && (i<length()));
					if(ret)
					{
						e = m_array[i];
					}
					return ret;
			} 
			T &operator [] (int i)
			{
				if ((0<=i) && (i<length()))
				{
					return m_array[i];
				}
				else
				{
					THROW_EXPECTION(IndexOutofBoundsExpection,"Parator i is invliad ... ");
				}
			}
			T operator[] (int i) const
			{
				return (const_cast<Array <T>&>(*this))[i];
			}
			T *array()const  //直接返回数组元素的首地址 
			{
				return m_array;
			}
			virtual int length() const = 0;
	}; 
}

#endif
