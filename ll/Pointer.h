#ifndef  POINTER_HH_
#define POINTER_HH_
#include "Object.h"
namespace DTLib{
	template <typename T>
	class Pointer: public Object
	{
		protected:
			T *m_pointer;
		public:
			Pointer(T*p = NULL)
			{
				m_pointer = p;
			}
			T *operator ->()
			{
				return m_pointer;
			}
			const T *operator ->() const
			{
				return m_pointer;
			}
			const T &operator *() const
			{
				return *m_pointer;
			}
			T &operator *()
			{
				return *m_pointer;
			}
			bool isNull() const
			{
				return (m_pointer == NULL);
			}
			T *get() const
			{
				return m_pointer;
			}
	};
	
}

#endif
