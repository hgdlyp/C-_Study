#ifndef LIST_H
#define LIST_H
#include"Object.h"
namespace DTLib{
template <typename T>
	class List :public Object
	{
		protected:
			List (const List&);        // ��ֹ�������츳ֵ���� ����ֹ����ָ��ѿռ� 
			List &operator = (const List&);  //���������غ���
	public:
		List()
		{
		}   //�ֹ���ӹ��캯�����������Ͳ����Լ���ӹ��캯���� 
		virtual bool insert(const T&e) = 0; //Ĭ��ֱ�������Ա���β������Ԫ�ء� 
		virtual bool insert( int i,const T&e) = 0;
		virtual bool remove( int i) = 0;
		virtual bool set( int i, const T&e)	= 0;
		virtual bool get( int i, T&e) const = 0;
		virtual int  find(const T &e) const = 0; 
		virtual int  length() const = 0;
		virtual void clear () = 0;
	};

}

#endif  /* LIST_H */
