#pragma once
#include <iostream>
#include <initializer_list>
#include "globals.h"

namespace Containers {

	template<typename T>
	class Vector {
	public:
		Vector() :
			m_data(nullptr), m_size(0), m_capacity(Global::VECTOR_INIT_SIZE)
		{
			allocate(Global::VECTOR_INIT_SIZE);
		}

		Vector(size_t size) :
			m_size(size), m_capacity(size)
		{
			allocate(size);
		}

		Vector(size_t size, const T& init_val) :
			m_size(size), m_capacity(size)
		{
			allocate(size);
			fill_n(size, init_val);
		}

		Vector(std::initializer_list<T> l) :
			m_size(l.size()), m_capacity(l.size())
		{
			allocate(l.size());
			fill_range(l.begin(), l.end());
		}

		Vector(const Vector& other) :
			m_size(other.m_size), m_capacity(other.m_capacity)
		{
			allocate(other.m_size);
			fill_range(other.begin(), other.end());
		}

		Vector(Vector&& other) :
			m_size(other.m_size), m_capacity(other.m_capacity)
		{
			allocate(other.m_size);
			fill_range(other.begin(), other.end());
		}

		~Vector() {
			if (m_data) delete[] m_data;
			m_capacity = 0;
			m_size = 0;
		}

		size_t size() const;

		bool empty() const;

		void push_back(const T&);

		void push_back(T&&);

		void pop_back();

		T& operator[](size_t);
		
		const T& operator[](size_t) const;

		class Iterator {
		public:
			Iterator() : m_pointer(nullptr) {}
			Iterator(T* pointer) : m_pointer(pointer) {}
			Iterator(const Iterator& other) : m_pointer(other.m_pointer) {}

			bool operator==(const Iterator&);

			bool operator!=(const Iterator&);

			Iterator& operator++();

			Iterator operator++(int);

			Iterator operator+(int);

			Iterator& operator+=(int);

			Iterator& operator--();

			Iterator operator--(int);

			Iterator operator-(int);

			Iterator& operator-=(int);

			size_t operator-(const Iterator&) const;

			T& operator*();

			T* operator->();

		private:
			T* m_pointer;
		};

		Iterator begin() const;

		Iterator end() const;

	private:
		T* m_data;
		size_t m_size;
		size_t m_capacity;

		void allocate(size_t);

		void fill_n(size_t, const T&);

		void resize(size_t);

		template<class IT>
		void fill_range(IT, IT);
	};


	template<typename T>
	size_t Vector<T>::size() const { return m_size; }

	template<typename T>
	bool Vector<T>::empty() const { return m_size == 0; }

	template<typename T>
	void Vector<T>::push_back(const T& value) {
		if (m_size == m_capacity) {
			resize(m_capacity * Global::VECTOR_RESIZE_FACTOR);
		}
		m_data[m_size] = value;
		++m_size;
	}

	template<typename T>
	void Vector<T>::push_back(T&& value) {
		if (m_size == m_capacity) {
			resize(m_capacity * Global::VECTOR_RESIZE_FACTOR);
		}
		m_data[m_size] = value;
		++m_size;
	}

	template<typename T>
	void Vector<T>::pop_back() {
		--m_size;
	}

	template<typename T>
	T& Vector<T>::operator[](size_t pos) {
		return m_data[pos];
	}

	template<typename T>
	const T& Vector<T>::operator[](size_t pos) const {
		return m_data[pos];
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const {
		return Vector<T>::Iterator(m_data);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::end() const {
		return Iterator(m_data + m_size);
	}

	template<typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& other)
	{
		return m_pointer == other.m_pointer;
	}

	template<typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& other)
	{
		return m_pointer != other.m_pointer;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		++m_pointer;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator it = *this;
		++(*this);
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int steps)
	{
		Iterator it = *this;
		m_pointer += steps;
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator+=(int steps)
	{
		m_pointer += steps;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator--()
	{
		--m_pointer;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
	{
		Iterator it = *this;
		--(*this);
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int steps)
	{
		Iterator it = *this;
		m_pointer -= steps;
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator-=(int steps)
	{
		m_pointer -= steps;
		return *this;
	}

	template<typename T>
	size_t Vector<T>::Iterator::operator-(const Vector<T>::Iterator& other) const
	{
		return m_pointer - other.m_pointer;
	}

	template<typename T>
	T& Vector<T>::Iterator::operator*()
	{
		return *m_pointer;
	}

	template<typename T>
	T* Vector<T>::Iterator::operator->()
	{
		return m_pointer;
	}

	template<typename T>
	void Vector<T>::allocate(size_t size) {
		m_data = new T[size];
	}

	template<typename T>
	void Vector<T>::fill_n(size_t size, const T& value) {
		for (size_t i = 0; i < size; ++i)
			m_data[i] = value;
	}

	template<typename T>
	void Vector<T>::resize(size_t capacity) {
		T* new_data = new T[capacity];
		size_t copy_capacity = capacity < m_capacity ?
			capacity : m_capacity;
		for (size_t i = 0; i < copy_capacity; ++i) {
			new_data[i] = m_data[i];
		}
		if (m_data) delete[] m_data;
		m_data = new_data;
		m_capacity = capacity;
	}

	template<typename T> template<class IT>
	void Vector<T>::fill_range(IT begin, IT end) {
		size_t i = 0;
		for (IT it = begin; it != end; ++it, ++i) {
			m_data[i] = *it;
		}
	}
}