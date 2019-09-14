#define _CRT_SECURE_NO_WARNINGS
#include"expection.h"
#include<cstring>
#include<cstdlib>

namespace DTLib{
	
	void Expection::init(const char *message,const char *file,int line)
	{
		m_message = (message ? _strdup(message) :NULL);
		
		if(file != NULL)
		{
			char sl[16] = {0};
			_itoa_s( line, sl, 10);
			m_location = static_cast<char*>(malloc(strlen(file) + strlen(sl) + 2));
			m_location = strcpy( m_location, file);
			m_location = strcat( m_location, ":");
			m_location = strcat( m_location, sl );
		}
		else
		{
			m_location = NULL;
		}
	}
	Expection::Expection(const char *message)
	{
		init(message,NULL,0);
	}
	Expection::Expection(const char *file, int line)
	{
		init(NULL,file,line);

	}
	Expection::Expection(const char *message,const char *file,int line)
	{
		init(message,file,line);
	}
			
    Expection::Expection(const Expection &e)
    {
    	m_message = _strdup(e.m_message);
    	m_location = _strdup(e.m_location);
	}
	Expection & Expection::operator = (const Expection &e )
	{
		if (this != &e)
		{
			free(m_message);
			free(m_location);
		
			m_message = _strdup(e.m_message);
    		m_location = _strdup(e.m_location);
		}
		return *this ;
	}
    const char *Expection::message() const
    {
    	return m_message;
	}
    const char *Expection::location() const
    {
    	return m_location;
	}
	Expection::~Expection() 
	{
		free(m_message);
		free(m_location);
	}
}
