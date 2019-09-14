#include <iostream>
#include "Object.h"
#include <cstdlib>
using namespace std;
namespace DTLib{
	void * Object::operator new(size_t size) throw()
	{
		//cout<<"object::operator new"<<endl;
		return malloc(size);
	}
	void Object::operator delete(void *p)
	{
		//cout<<"object::operator delete"<<endl;
		free(p);
	}
	void *Object::operator new[](size_t size) throw()
	{
	    //cout<<"object::operator new[]"<<endl;

		return malloc(size);
	}
	bool Object::operator == (const Object &obj)
	{
		return (this == &obj);
	}
	bool Object::operator != (const Object &obj)
	{
		return (this != &obj);

	}
	void Object::operator delete[] (void *p)
	{
		//cout<<"object::operator delete[]"<<endl;
		free(p);
	}
	Object::~Object()
	{
		
	}
}
