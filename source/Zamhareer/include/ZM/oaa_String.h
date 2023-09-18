#ifndef OAA_STRING_H
#define OAA_STRING_H

#include <cstring>
#include <fstream>

namespace OAA
{
	class String
	{
		public:
			String(const char *s);
			String(const String &s);
			void operator=(const String &other);
			void operator=(const char *other);
			const char * cstr();
			inline size_t len() const {return m_Lenght-1;}
			String operator +(const String &s);
			String operator +(const char *s);
			void operator +=(const String &s);
			void operator +=(const char *s);
			~String();
		private:
			String(char *c_str, size_t lenght);
			char *m_CString;
			size_t m_Lenght;
	};
	String LoadFile(const char *path, int *state);
}

#ifdef OAA_STRING_IMPL
namespace OAA
{
	String::String(char *c_str, size_t lenght)
		:m_CString(c_str), m_Lenght(lenght){
	}
	String::String(const String &s)
	{
		m_Lenght = s.m_Lenght;
		m_CString = new char[m_Lenght];
		memcpy(m_CString, s.m_CString, sizeof(char)*m_Lenght);

	}
	String::String(const char *s)
		:m_Lenght(strlen(s)+1)
	{
		m_CString = new char[m_Lenght];
		memcpy(m_CString, s, sizeof(char)*m_Lenght);
	}
	void String::operator=(const String &other)
	{
		m_Lenght = other.m_Lenght;
		char *newdata = new char[m_Lenght];
		memcpy(newdata, other.m_CString, sizeof(char)*m_Lenght);
		m_CString = newdata;
	}
	void String::operator=(const char *other)
	{
		m_Lenght = strlen(other)+1;
		char *newdata = new char[m_Lenght];
		memcpy(newdata, other, sizeof(char)*m_Lenght);
		m_CString = newdata;
	}
	String::~String()
	{
		if(m_CString)
			delete[] m_CString;
	}
	const char *String::cstr()
	{
		return m_CString;
	}

	String String::operator +(const String &s)
	{
		size_t lenght = m_Lenght + s.m_Lenght - 1;
		char *data = new char[lenght];
		memcpy(data, m_CString, sizeof(char)*(m_Lenght-1));
		memcpy(data+m_Lenght-1, s.m_CString, sizeof(char)*s.m_Lenght);
		return String(data, lenght);
	}
	String String::operator +(const char *s)
	{
		size_t lenght = strlen(s) + m_Lenght;
		char *data = new char[lenght];
		memcpy(data, m_CString, sizeof(char)*(m_Lenght-1));
		memcpy(data+m_Lenght-1, s, sizeof(char)*strlen(s)+1);
		return String(data, lenght);
	}
	void String::operator +=(const String &s)
	{
		size_t lenght = m_Lenght + s.m_Lenght - 1;
		char *data = new char[lenght];
		memcpy(data, m_CString, sizeof(char)*(m_Lenght-1));
		memcpy(data+m_Lenght-1, s.m_CString, sizeof(char)*s.m_Lenght);
		m_Lenght = lenght;
		m_CString = data;
	}
	void String::operator +=(const char *s)
	{
		size_t lenght = strlen(s) + m_Lenght - 1;
		char *data = new char[lenght];
		memcpy(data, m_CString, sizeof(char)*(m_Lenght-1));
		memcpy(data+m_Lenght-1, s, sizeof(char)*strlen(s));
		m_Lenght = lenght;
		m_CString = data;
	}
	String LoadFile(const char * path, int *state )
	{
		*state = 0;
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if(!file.is_open())
		{
			*state = 1;
		}
		std::streampos size = file.tellg();
		file.seekg(0, std::ios::beg);
		char buffer[(int)size];
		file.read(buffer, size);
		buffer[(int)size-1] = '\0';
		if(file.bad())
		{
			*state = 1;
		}
		if(*state) return String("");
		return String(buffer);
	}
}

#endif // 

#endif // OAA_STRING_H
