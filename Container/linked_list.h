#pragma once
#include <initializer_list>
#include <iostream>
#include <utility>
#include "globals.h"
#include "exception.h"

namespace Containers {

	template<typename T>
	class LinkedList {
	public:
		LinkedList() :
			m_head(nullptr), m_tail(new ListNode()), m_size(0) {}

		LinkedList(size_t size, const T& init_val) :
			LinkedList() {
			insert_n(nullptr, size, init_val);
		}

		LinkedList(std::initializer_list<T> il) :
			LinkedList() {
			insert_range(nullptr, il.begin(), il.end());
		}

		LinkedList(const LinkedList& other) :
			LinkedList() {
			insert_range(0, other.begin(), other.end());
		}

		LinkedList(LinkedList&& other) :
			LinkedList() {
			insert_range(0, other.begin(), other.end());
		}

		~LinkedList() {
			while (size()) pop_back();
			delete m_tail;
		}

		size_t size() const;

		bool empty() const;

		void push_back(const T&);

		void push_back(T&&);

		void push_front(const T&);

		void push_front(T&&);

		template<typename...Args>
		void emplace_back(Args&&...);

		template<typename...Args>
		void emplace_front(Args&&...);

		void pop_back();

		void pop_front();

		T& front();
		
		const T& front() const;

		T& back();

		const T& back() const;

		class Iterator {
		public:
			Iterator() : m_pointer(nullptr) {}

			Iterator(struct ListNode* pointer) : m_pointer(pointer) {}

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
			struct ListNode* m_pointer;
			friend class LinkedList;
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
		struct ListNode {
			T value;
			ListNode* next;
			ListNode* prev;
			ListNode() : prev(nullptr), next(nullptr) {}
			ListNode(const T& value) :
				value(value), prev(nullptr), next(nullptr) {}
			ListNode(T&& value) :
				value(std::move(value)), prev(nullptr), next(nullptr) {}
		};

		ListNode* m_head;
		ListNode* m_tail;
		size_t m_size;

		void insert_between(ListNode*, ListNode*, ListNode*);

		void erase(ListNode*);

		void insert_n(ListNode*, size_t, const T&);

		template<class IT>
		void insert_range(ListNode*, IT, IT);
	};

	template<typename T>
	void LinkedList<T>::insert_n(ListNode* start, size_t n, const T& value) {
		for (size_t i = 0; i < n; ++i)
			push_back(value);
	}

	template<typename T>
	template<class IT>
	void LinkedList<T>::insert_range(ListNode* start, IT first, IT last) {
		for (IT it = first; it != last; ++it)
			push_back(*it);
	}

	template<typename T>
	void LinkedList<T>::insert_between(ListNode* new_node, ListNode* prev, ListNode* next) {
		new_node->prev = prev;
		new_node->next = next;
		if (prev) prev->next = new_node;
		else m_head = new_node;
		next->prev = new_node;
		++m_size;
	}

	template<typename T>
	size_t LinkedList<T>::size() const { return m_size; }

	template<typename T>
	bool LinkedList<T>::empty() const { return m_size == 0; }

	template<typename T>
	void LinkedList<T>::push_back(const T& value) {
		ListNode* new_node = new ListNode(value);
		insert_between(new_node, m_tail->prev, m_tail);
	}

	template<typename T>
	void LinkedList<T>::push_back(T&& value) {
		ListNode* new_node = new ListNode(std::move(value));
		insert_between(new_node, m_tail->prev, m_tail);
	}

	template<typename T>
	void LinkedList<T>::push_front(const T& value) {
		ListNode* new_node = new ListNode(value);
		insert_between(new_node, nullptr, m_head);
	}

	template<typename T>
	void LinkedList<T>::push_front(T&& value) {
		ListNode* new_node = new ListNode(std::move(value));
		insert_between(new_node, nullptr, m_head);
	}

	template<typename T>
	template<typename...Args>
	void LinkedList<T>::emplace_back(Args&&...args) {
		ListNode* new_node = new ListNode(T(std::forward<Args>(args)...));
		insert_between(new_node, m_tail->prev, m_tail);
	}

	template<typename T>
	template<typename...Args>
	void LinkedList<T>::emplace_front(Args&&...args) {
		ListNode* new_node = new ListNode(T(std::forward<Args>(args)...));
		insert_between(new_node, nullptr, m_head);
	}

	template<typename T>
	T& LinkedList<T>::front() {
		if (!m_head) throw OutOfRangeException("LinkedList");
		return m_head->value;
	}

	template<typename T>
	const T& LinkedList<T>::front() const {
		if (!m_head) throw OutOfRangeException("LinkedList");
		return m_head->value;
	}

	template<typename T>
	T& LinkedList<T>::back() {
		if (!m_tail->prev) throw OutOfRangeException("LinkedList");
		return m_tail->prev->value;
	}

	template<typename T>
	const T& LinkedList<T>::back() const {
		if (!m_tail->prev) throw OutOfRangeException("LinkedList");
		return m_tail->prev->value;
	}

	template<typename T>
	void LinkedList<T>::erase(ListNode* node) {
		if (!node) throw OutOfRangeException("LinkedList");
		if (node->prev)
			node->prev->next = node->next;
		else 
			m_head = node->next;
		node->next->prev = node->prev;
		delete node;
		--m_size;
	}

	template<typename T>
	void LinkedList<T>::pop_back() {
		erase(m_tail->prev);
	}

	template<typename T>
	void LinkedList<T>::pop_front() {
		erase(m_head);
	}

	template<typename T>
	bool LinkedList<T>::Iterator::operator==(const Iterator& other) const {
		return m_pointer == other.m_pointer;
	}

	template<typename T>
	bool LinkedList<T>::Iterator::operator!=(const Iterator& other) const {
		return m_pointer != other.m_pointer;
	}

	template<typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
		if (!m_pointer->next) throw OutOfRangeException("LinkedList");
		m_pointer = m_pointer->next;
		return *this;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
		Iterator it = *this;
		++(*this);
		return it;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator+(int steps) const {
		Iterator it = *this;
		for (int i = 0; i < steps; ++i, ++it);
		return it;
	}

	template<typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator+=(int steps) {
		*this = *this + steps;
		return *this;
	}

	template<typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--() {
		if (!m_pointer->prev) throw OutOfRangeException("LinkedList");
		m_pointer = m_pointer->prev;
		return *this;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int) {
		Iterator it = *this;
		--(*this);
		return it;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator-(int steps) const {
		Iterator it = *this;
		for (int i = 0; i < steps; ++i, --it);
		return it;
	}

	template<typename T>
	typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator-=(int steps) {
		*this = *this - steps;
		return *this;
	}

	template<typename T>
	size_t LinkedList<T>::Iterator::operator-(const Iterator& other) const {
		size_t dis = 0;
		for (Iterator it = other; it.m_pointer; ++it, ++dis) {
			if (m_pointer == it.m_pointer) return dis;
		}
		throw InvalidIteratorException("LinkedList");
	}

	template<typename T>
	T& LinkedList<T>::Iterator::operator*() {
		return m_pointer->value;
	}

	template<typename T>
	const T& LinkedList<T>::Iterator::operator*() const {
		return m_pointer->value;
	}

	template<typename T>
	T* LinkedList<T>::Iterator::operator->() {
		return &(m_pointer->value);
	}

	template<typename T>
	const T* LinkedList<T>::Iterator::operator->() const {
		return &(m_pointer->value);
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::begin() {
		return Iterator(m_head);
	}

	template<typename T>
	const typename LinkedList<T>::Iterator LinkedList<T>::begin() const {
		return Iterator(m_head);
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::end() {
		return Iterator(m_tail);
	}

	template<typename T>
	const typename LinkedList<T>::Iterator LinkedList<T>::end() const {
		return Iterator(m_tail);
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::find(const T& value) const {
		for (Iterator it = begin(); it != end(); ++it) {
			if (*it == value) return it;
		}
		return end();
	}

	template<typename T>
	template<typename...Args>
	typename LinkedList<T>::Iterator LinkedList<T>::emplace(const Iterator pos, Args&&...args) {
		ListNode* new_node = new ListNode(std::forward<Args>(args)...);
		insert_between(new_node, pos.m_pointer->prev, pos.m_pointer);
		return Iterator(new_node);
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::insert(const Iterator pos, const T& value) {
		insert(pos, (size_t) 1, value);
		return pos - 1;
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::insert(const Iterator pos, T&& value) {
		return emplace(pos, std::move(value));
	}

	template<typename T>
	void LinkedList<T>::insert(const Iterator pos, size_t n, const T& value) {
		ListNode* ptr = pos.m_pointer;
		for (size_t i = 0; i < n; ++i) {
			ListNode* new_node = new ListNode(value);
			insert_between(new_node, pos.m_pointer->prev, pos.m_pointer);
		}
	}

	template<typename T>
	template<class IT>
	void LinkedList<T>::insert(const Iterator pos, IT first, IT last) {
		Iterator cur = pos;
		for (IT it = first; it != last; ++it) {
			cur = ++insert(cur, *it);
		}
	}

	template<typename T>
	void LinkedList<T>::insert(const Iterator pos, std::initializer_list<T> il) {
		insert(pos, il.begin(), il.end());
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::erase(const Iterator pos) {
		erase(pos.m_pointer);
	}

	template<typename T>
	typename LinkedList<T>::Iterator LinkedList<T>::erase(const Iterator first, const Iterator last) {
		size_t dis = last - first;
		for (Iterator it = first; it != last; ++it) {
			erase(it);
		}
		return first;
	}
}