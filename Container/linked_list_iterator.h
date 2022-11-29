#pragma once
#include "exception.h"

namespace Containers {

	template<typename T, template<typename...T> class CT>
	class LinkedListIterator {
	public:
		LinkedListIterator() : m_pointer(nullptr) {}

		LinkedListIterator(CT<T>::Node* pointer) : m_pointer(pointer) {}

		LinkedListIterator(const LinkedListIterator& other) : m_pointer(other.m_pointer) {}

		bool operator==(const LinkedListIterator&) const;

		bool operator!=(const LinkedListIterator&) const;

		LinkedListIterator& operator++();

		LinkedListIterator operator++(int);

		LinkedListIterator operator+(int) const;

		LinkedListIterator& operator+=(int);

		LinkedListIterator& operator--();

		LinkedListIterator operator--(int);

		LinkedListIterator operator-(int) const;

		LinkedListIterator& operator-=(int);

		size_t operator-(const LinkedListIterator&) const;

		T& operator*();

		const T& operator*() const;

		T* operator->();

		const T* operator->() const;

	private:
		friend class CT<T>;
		CT<T>::Node* m_pointer;
	};

	// LinkedListIterators
	template<typename T, template<typename...T> class CT>
	bool LinkedListIterator<T, CT>::operator==(const LinkedListIterator& other) const {
		return m_pointer == other.m_pointer;
	}

	template<typename T, template<typename...T> class CT>
	bool LinkedListIterator<T, CT>::operator!=(const LinkedListIterator& other) const {
		return m_pointer != other.m_pointer;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT>& LinkedListIterator<T, CT>::operator++() {
		if (!m_pointer->next) throw OutOfRangeException("LinkedList");
		m_pointer = m_pointer->next;
		return *this;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT> LinkedListIterator<T, CT>::operator++(int) {
		LinkedListIterator it = *this;
		++(*this);
		return it;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT> LinkedListIterator<T, CT>::operator+(int steps) const {
		LinkedListIterator it = *this;
		for (int i = 0; i < steps; ++i, ++it);
		return it;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT>& LinkedListIterator<T, CT>::operator+=(int steps) {
		*this = *this + steps;
		return *this;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT>& LinkedListIterator<T, CT>::operator--() {
		if (!m_pointer->prev) throw OutOfRangeException("LinkedList");
		m_pointer = m_pointer->prev;
		return *this;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT> LinkedListIterator<T, CT>::operator--(int) {
		LinkedListIterator it = *this;
		--(*this);
		return it;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT> LinkedListIterator<T, CT>::operator-(int steps) const {
		LinkedListIterator it = *this;
		for (int i = 0; i < steps; ++i, --it);
		return it;
	}

	template<typename T, template<typename...T> class CT>
	typename LinkedListIterator<T, CT>& LinkedListIterator<T, CT>::operator-=(int steps) {
		*this = *this - steps;
		return *this;
	}

	template<typename T, template<typename...T> class CT>
	size_t LinkedListIterator<T, CT>::operator-(const LinkedListIterator& other) const {
		size_t dis = 0;
		for (LinkedListIterator it = other; it.m_pointer; ++it, ++dis) {
			if (m_pointer == it.m_pointer) return dis;
		}
		throw InvalidIteratorException("LinkedList");
	}

	template<typename T, template<typename...T> class CT>
	T& LinkedListIterator<T, CT>::operator*() {
		return m_pointer->value;
	}

	template<typename T, template<typename...T> class CT>
	const T& LinkedListIterator<T, CT>::operator*() const {
		return m_pointer->value;
	}

	template<typename T, template<typename...T> class CT>
	T* LinkedListIterator<T, CT>::operator->() {
		return &(m_pointer->value);
	}

	template<typename T, template<typename...T> class CT>
	const T* LinkedListIterator<T, CT>::operator->() const {
		return &(m_pointer->value);
	}

}