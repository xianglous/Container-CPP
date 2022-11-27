#pragma once
#include <initializer_list>
#include <iostream>
#include <utility>
#include "globals.h"
#include "exception.h"

namespace Containers {

	template<typename T>
	class Vector {
	public:
		Vector() :
			m_data(nullptr), m_size(0), m_capacity(Global::VECTOR_INIT_SIZE) {
			allocate(Global::VECTOR_INIT_SIZE);
		}

		Vector(size_t size) :
			m_size(size), m_capacity(size) {
			allocate(size);
		}

		Vector(size_t size, const T& init_val) :
			m_size(size), m_capacity(size) {
			allocate(size);
			fill_n(0, size, init_val);
		}

		Vector(std::initializer_list<T> il) :
			m_size(il.size()), m_capacity(il.size()) {
			allocate(il.size());
			fill_range(0, il.begin(), il.end());
		}

		Vector(const Vector& other) :
			m_size(other.m_size), m_capacity(other.m_capacity) {
			allocate(other.m_size);
			fill_range(0, other.begin(), other.end());
		}

		Vector(Vector&& other) :
			m_size(other.m_size), m_capacity(other.m_capacity) {
			allocate(other.m_size);
			fill_range(0, other.begin(), other.end());
		}

		~Vector() {
			if (m_data) delete[] m_data;
			m_capacity = 0;
			m_size = 0;
		}

		size_t size() const;

		bool empty() const;

		void reserve(size_t);

		void resize(size_t);

		void resize(size_t, const T&);

		void shrink_to_fit();

		void swap(Vector& other) noexcept;

		void push_back(const T&);

		void push_back(T&&);

		template<typename...Args>
		void emplace_back(Args&&...);

		void pop_back();

		T& operator[](size_t);

		const T& operator[](size_t) const;

		T& front();

		const T& front() const;

		T& back();

		const T& back() const;

		class Iterator {
		public:
			Iterator() : m_pointer(nullptr) {}

			Iterator(T* pointer) : m_pointer(pointer) {}

			Iterator(const Iterator& other) : m_pointer(other.m_pointer) {}

			bool operator==(const Iterator&) const;

			bool operator!=(const Iterator&) const;

			Iterator& operator++();

			Iterator operator++(int);

			Iterator operator+(int) const;

			Iterator& operator+=(int);

			Iterator& operator--();

			Iterator operator--(int);

			Iterator operator-(int) const;

			Iterator& operator-=(int);

			size_t operator-(const Iterator&) const;

			T& operator*();

			const T& operator*() const;

			T* operator->();

			const T* operator->() const;

		private:
			T* m_pointer;
		};

		Iterator begin();

		const Iterator begin() const;

		Iterator end();

		const Iterator end() const;

		Iterator find(const T&) const;

		template<typename...Args>
		Iterator emplace(const Iterator, Args&&...);

		Iterator insert(const Iterator, const T&);

		Iterator insert(const Iterator, T&&);

		void insert(const Iterator, size_t, const T&);

		template<class IT>
		void insert(const Iterator, IT, IT);

		void insert(const Iterator, std::initializer_list<T>);

		Iterator erase(const Iterator);

		Iterator erase(const Iterator, const Iterator);

	private:
		T* m_data;
		size_t m_size;
		size_t m_capacity;

		void allocate(size_t);

		void fill_n(size_t, size_t, const T&);

		template<class IT>
		void fill_range(size_t, IT, IT);
	};


	template<typename T>
	size_t Vector<T>::size() const { return m_size; }

	template<typename T>
	bool Vector<T>::empty() const { return m_size == 0; }

	template<typename T>
	void Vector<T>::push_back(const T& value) {
		if (m_size == m_capacity) {
			reserve(m_capacity * Global::VECTOR_RESIZE_FACTOR);
		}
		m_data[m_size] = value;
		++m_size;
	}

	template<typename T>
	void Vector<T>::push_back(T&& value) {
		emplace_back(std::move(value));
	}

	template<typename T>
	template<typename...Args>
	void Vector<T>::emplace_back(Args&&... args) {
		if (m_size == m_capacity) {
			reserve(m_capacity * Global::VECTOR_RESIZE_FACTOR);
		}
		m_data[m_size] = T(std::forward<Args>(args)...);
		++m_size;
	}

	template<typename T>
	void Vector<T>::pop_back() {
		if (m_size > 0) --m_size;
		else throw OutOfRangeException("Vector");
	}

	template<typename T>
	T& Vector<T>::operator[](size_t pos) {
		if (pos >= m_size) throw OutOfRangeException("Vector");
		return m_data[pos];
	}

	template<typename T>
	const T& Vector<T>::operator[](size_t pos) const {
		if (pos >= m_size) throw OutOfRangeException("Vector");
		return m_data[pos];
	}

	template<typename T>
	T& Vector<T>::front() {
		if (!m_size) throw OutOfRangeException("Vector");
		return m_data[0];
	}

	template<typename T>
	const T& Vector<T>::front() const {
		if (!m_size) throw OutOfRangeException("Vector");
		return m_data[0];
	}

	template<typename T>
	T& Vector<T>::back() {
		if (!m_size) throw OutOfRangeException("Vector");
		return m_data[m_size - 1];
	}

	template<typename T>
	const T& Vector<T>::back() const {
		if (!m_size) throw OutOfRangeException("Vector");
		return m_data[m_size - 1];
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::begin() {
		return Iterator(m_data);
	}

	template<typename T>
	const typename Vector<T>::Iterator Vector<T>::begin() const {
		return Iterator(m_data);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::end() {
		return Iterator(m_data + m_size);
	}

	template<typename T>
	const typename Vector<T>::Iterator Vector<T>::end() const {
		return Iterator(m_data + m_size);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::find(const T& value) const {
		for (Iterator it = begin(); it != end(); ++it) {
			if (*it == value) return it;
		}
		return end();
	}

	template<typename T>
	template<typename...Args>
	typename Vector<T>::Iterator Vector<T>::emplace(const Iterator pos, Args&&...args) {
		if (m_size == m_capacity) {
			reserve(m_size + 1);
		}
		size_t start = pos - begin();
		if (start >= m_size) throw InvalidIteratorException("Vector");
		for (size_t i = m_size; i > start; --i) {
			m_data[i] = m_data[i - 1];
		}
		*pos = T(std::forward<Args>(args)...);
		++m_size;
		return pos;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::insert(const Iterator pos, const T& value) {
		insert(pos, (size_t) 1, value);
		return pos;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::insert(const Iterator pos, T&& value) {
		return emplace(pos, std::move(value));
	}

	template<typename T>
	void Vector<T>::insert(const Iterator pos, size_t n, const T& value) {
		size_t start = pos - begin();
		if (m_size + n > m_capacity) {
			reserve(m_size + n);
		}
		if (start > m_size) throw InvalidIteratorException("Vector");
		for (size_t i = m_size; i > start; --i) {
			m_data[i + n - 1] = m_data[i - 1];
		}
		fill_n(start, n, value);
		m_size += n;
	}

	template<typename T> 
	template<class IT>
	void Vector<T>::insert(const Iterator pos, IT first, IT last) {
		size_t n = last - first;
		size_t start = pos - begin();
		size_t fi = &(*first) - m_data, la = &(*last) - m_data;
		if (m_size + n > m_capacity) {
			reserve(m_size + n);
		}
		if (start > m_size) throw InvalidIteratorException("Vector");
		for (size_t i = m_size; i > start; --i) {
			m_data[i + n - 1] = m_data[i - 1];
		}
		if (typeid(IT) == typeid(Iterator) && fi <= m_size && la <= m_size) {
			for (size_t i = fi; i < la; ++i) {
				m_data[start + i - fi] = m_data[i < start ? i : i + n];
			}
		}
		else
			fill_range(start, first, last);
		m_size += n;
	}

	template<typename T>
	void Vector<T>::insert(const Iterator pos, std::initializer_list<T> il) {
		insert(pos, il.begin(), il.end());
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::erase(const Iterator pos) {
		return erase(pos, pos + 1);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::erase(const Iterator first, const Iterator last) {
		if (first == last) return last;
		size_t start = first - begin(), end = last - begin();
		if (start > m_size || end > m_size) throw InvalidIteratorException("Vector");
		for (size_t i = end; i < m_size; ++i) {
			m_data[i - end + start] = m_data[i];
		}
		m_size -= end - start;
		return Iterator(m_data + start);
	}

	template<typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& other) const {
		return m_pointer == other.m_pointer;
	}

	template<typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& other) const {
		return m_pointer != other.m_pointer;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
		++m_pointer;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
		Iterator it = *this;
		++(*this);
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int steps) const {
		Iterator it = *this;
		it.m_pointer += steps;
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator+=(int steps) {
		m_pointer += steps;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
		--m_pointer;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
		Iterator it = *this;
		--(*this);
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int steps) const {
		Iterator it = *this;
		it.m_pointer -= steps;
		return it;
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator-=(int steps) {
		m_pointer -= steps;
		return *this;
	}

	template<typename T>
	size_t Vector<T>::Iterator::operator-(const Iterator& other) const {
		return m_pointer - other.m_pointer;
	}

	template<typename T>
	T& Vector<T>::Iterator::operator*() {
		return *m_pointer;
	}

	template<typename T>
	const T& Vector<T>::Iterator::operator*() const {
		return *m_pointer;
	}

	template<typename T>
	T* Vector<T>::Iterator::operator->() {
		return m_pointer;
	}

	template<typename T>
	const T* Vector<T>::Iterator::operator->() const {
		return m_pointer;
	}

	template<typename T>
	void Vector<T>::allocate(size_t size) {
		m_data = new T[size];
	}

	template<typename T>
	void Vector<T>::fill_n(size_t start, size_t size, const T& value) {
		for (size_t i = 0; i < size; ++i)
			m_data[i + start] = value;
	}

	template<typename T>
	void Vector<T>::reserve(size_t capacity) {
		if (capacity <= m_capacity) return;
		T* new_data = new T[capacity];
		for (size_t i = 0; i < m_capacity; ++i) {
			new_data[i] = m_data[i];
		}
		if (m_data) delete[] m_data;
		m_data = new_data;
		m_capacity = capacity;
	}

	template<typename T>
	void Vector<T>::resize(size_t size) {
		resize(size, T());
	}

	template<typename T>
	void Vector<T>::resize(size_t size, const T& value) {
		if (size < m_size)
			erase(begin() + size, end());
		else if (size > m_size)
			insert(end(), size - m_size, value);
	}

	template<typename T>
	void Vector<T>::shrink_to_fit() {
		T* new_data = new T[m_size];
		for (size_t i = 0; i < m_size; ++i) {
			new_data[i] = m_data[i];
		}
		if (m_data) delete[] m_data;
		m_data = new_data;
		m_capacity = m_size;
	}

	template<typename T>
	void Vector<T>::swap(Vector& other) noexcept;

	template<typename T> template<class IT>
	void Vector<T>::fill_range(size_t start, IT begin, IT end) {
		size_t i = 0;
		for (IT it = begin; it != end; ++it, ++i) {
			m_data[i + start] = *it;
		}
	}
}