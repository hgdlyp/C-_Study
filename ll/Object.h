
#ifndef OBJECT_H
#define OBJECT_H
namespace DTLib{
	class Object
	{
		public:
			void *operator new(size_t) throw();
			void operator delete(void *p);
			void *operator new[](size_t) throw();
			void operator delete[] (void *p); 
			bool operator == (const Object &obj);
			bool operator != (const Object &obj);

			virtual ~Object() = 0;
		protected:
	};
}


#endif   //OBJECT_H
