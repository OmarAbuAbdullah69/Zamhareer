#pragma once

#include <cstddef>
#include <cstring>
#include <initializer_list>
namespace ZM{
	template<typename T>
	class Orray
	{
		private:
			size_t m_Length = 0;
			T *m_Data = nullptr;
		public:
			Orray(){}
			Orray(size_t size);
			Orray(std::initializer_list<T> list);
			Orray(Orray<T> &&other);
			~Orray();
			void Clear();

			T &operator [](size_t index);
			size_t Lenght() const;

			int PushBack(T new_obj);
			int Insert(size_t i, T new_obj);
			T *begin() const;
			T *end() const;
	};

	template<typename T>
	Orray<T>::Orray(size_t size)
	{
		if(size <= 0)
			return;
		m_Length = size;
		m_Data = new T[size];

	}

	template<typename T>
	Orray<T>::Orray(std::initializer_list<T> list)
	{
		m_Length = list.size();
		m_Data = new T[m_Length];
		memcpy(m_Data, list.begin(), list.size()*sizeof(T));
	}


	template<typename T>
	Orray<T>::Orray(Orray<T> &&other)
	{
		m_Length = other.Lenght();
		m_Data = &other[0];
		other.Clear();
	}

	template<typename T>
	Orray<T>::~Orray()
	{
		delete[] m_Data;
	}

	template<typename T>
	void Orray<T>::Clear()
	{
		m_Data = nullptr;
		m_Length = 0;
	}

	template<typename T>
	size_t Orray<T>::Lenght() const
	{
		return m_Length;
	}


	template<typename T>
	T &Orray<T>::operator [](size_t index)
	{
		return m_Data[index];
	}

	template<typename T>
	int Orray<T>::PushBack(T new_obj)
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
	int Orray<T>::Insert(size_t i, T new_obj)
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
	T *Orray<T>::begin() const 
	{
		return m_Data;
	}

	template<typename T>
	T *Orray<T>::end() const 
	{
		return m_Data+m_Length;
	}

}
