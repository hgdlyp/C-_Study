#ifndef SEQLIST_H__
#define SEQLIST_H__
#include "List.h"
#include "expection.h"
namespace DTLib{
	template <typename T>
class SeqList:public List <T>
{
	protected :
		T *m_array;   //ʹ��һά����ʵ�������˳��洢�ṹ
		int m_length;
	public:
		bool insert( int i,const T&e) //Ԫ�غ��
		{
			int p = 0;
			bool ret = ((0<=i) && (i<= m_length));
			ret = ret && (m_length < capacity());
			if(ret)
			{
				for(p = m_length - 1; p>=i; p--)    /* ����Ԫ���Ǵ�0��ʼ�ģ����� */
				{
					m_array[p+1] = m_array[p];
				}
				m_array[i] = e; 
				m_length++;
			}
			return ret;

		}
		bool insert(const T&e)//Ԫ��Ϊ���
		{
			return insert(m_length ,e) ; 
		}
		 
		bool remove( int i) 
		{
			int p = 0;
			bool ret = ((0<=i) && (i< m_length));
			if(ret)
			{
				for(p=i;p<m_length - 1;p++)
				{
					m_array[p] = m_array[p + 1]; 
				}
				m_length--;
			}
			return ret;

		}
	 	bool set( int i, const T&e)   /* ��������Ŀ��λ��Ԫ�ص�ֵ */
	 	{
	 		bool ret = ((0<=i) && (i< m_length));
	 		if(ret)
	 		{
	 			m_array[i] = e;
			}
			return ret;
 	
		} 
		int find(const T &e) const
		{
			int ret = -1;
			for(int i=0;i<length();i++)
			{
				if(m_array[i] == e)
				{
					ret = i;
					break;
				}
			}	
			return i;
		}
	    bool get( int i, T&e) const
	    {
	    	bool ret = ((0<=i) && (i< m_length));
	 		if(ret)
	 		{
	 			e = m_array[i];
			}
			return ret;
		}
		int length(void) const
		{
			return m_length;
		}
	    void clear(void)
	    {
	     	m_length = 0;
		}
	    
	    //˳��洢���Ա�Ĵ洢��ʽ
		T &operator[] (int i) //������[]����
		{
			if ((0<=i) && (i< m_length))
			{
				return m_array[i];
			}
			else
			{
				THROW_EXPECTION(IndexOutofBoundsExpection,"paramter i is invliad");
			}
		}
		T operator[] (int i) const
		{
			return (const_cast<SeqList<T> &>(*this))[i];   /* ���ö����const ����ȥ����ֱ��ʹ������ĺ��� */
		}
		/* ˳��洢�ṹ�Ĵ洢������С */
		virtual int capacity() const
		{
				
		} 

};		
}

#endif /*SEQLIST_H__*/
