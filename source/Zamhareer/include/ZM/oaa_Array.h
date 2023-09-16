#ifndef OAA_Array_Header
#define OAA_Array_Header

#include <cstddef>
#include <cstring>
#include <initializer_list>

namespace OAA
{

	template<typename T>
	class Array
	{
		private:
			size_t m_Length = 0;
			T *m_Data = nullptr;
		public:
			Array();
			Array(const Array<T> &other);
			Array(size_t size);
			Array(std::initializer_list<T> list);
			Array(Array<T> &&other);
			~Array();
			void Clear();

			T &operator [](size_t index);
			size_t Length() const;

			int PushBack(T new_obj);
			int Insert(size_t i, T new_obj);
			T *begin() const;
			T *end() const;
	};

	template<typename T>
	Array<T>::Array(){}
	
	template<typename T>
	Array<T>::Array(const Array<T> &other)
	{
		m_Length = other.m_Length;
		memcpy(m_Data, other.m_Data, sizeof(T)*m_Length);
	}

	template<typename T>
	Array<T>::Array(size_t size)
	{
		if(size <= 0)
			return;
		m_Length = size;
		m_Data = new T[size];

	}

	template<typename T>
	Array<T>::Array(std::initializer_list<T> list)
	{
		m_Length = list.size();
		m_Data = new T[m_Length];
		memcpy(m_Data, list.begin(), list.size()*sizeof(T));
	}


	template<typename T>
	Array<T>::Array(Array<T> &&other)
	{
		m_Length = other.Length();
		m_Data = &other[0];
		other.Clear();
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete[] m_Data;
	}

	template<typename T>
	void Array<T>::Clear()
	{
		m_Data = nullptr;
		m_Length = 0;
	}

	template<typename T>
	size_t Array<T>::Length() const
	{
		return m_Length;
	}


	template<typename T>
	T &Array<T>::operator [](size_t index)
	{
		return m_Data[index];
	}

	template<typename T>
	int Array<T>::PushBack(T new_obj)
	{
		T *new_pos = new T[m_Length+1];
		if(!new_pos)
			return -1;
		memmove(new_pos, m_Data, m_Length * sizeof(T));
		m_Data = new_pos;
		m_Data[m_Length] = new_obj;
		m_Length++;
		return 0;
	}

	template<typename T>
	int Array<T>::Insert(size_t i, T new_obj)
	{
		if(i >= m_Length)
			return -1;
		T *new_pos = new T[m_Length+1];
		memmove(new_pos, m_Data, i*sizeof(T));
		memmove(new_pos+i+1, m_Data+i, (m_Length-i)*sizeof(T));
		m_Data = new_pos;
		m_Data[i] = new_obj;
		m_Length++;
		return 0;
	}

	template<typename T>
	T *Array<T>::begin() const 
	{
		return m_Data;
	}

	template<typename T>
	T *Array<T>::end() const 
	{
		return m_Data+m_Length;
	}
}
#endif // Array_Header
