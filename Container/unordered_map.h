#pragma once
#include <functional>
#include <utility>
#include <initializer_list>

namespace Containers {
	template<
		typename K, typename V,
		typename Hash = std::hash<K>,
		typename Equal = std::equal_to<K>>
		class UnorderedMap {
		public:
			typedef typename std::pair<const K, V> value_type;

			UnorderedMap();

			UnorderedMap(std::initializer_list<value_type>);

			template<class IT>
			UnorderedMap(IT, IT);

			UnorderedMap(const UnorderedMap&);

			UnorderedMap(UnorderedMap&&);

			~UnorderedMap();

			size_t size() const;

			V& operator[](const K&);

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

			T& operator*() const;

			T* operator->() const;

		private:
			value_type* m_pointer;
		};

		Iterator begin() const;

		Iterator end() const;

		Iterator find(const K&) const;

		std::pair<Iterator, bool> insert(const value_type&);
		
		std::pair<Iterator, bool> insert(value_type&&);

		template<class IT>
		void insert(IT, IT);

		void insert(std::initializer_list<value_type>);

	private:
		value_type* m_data;
		size_t m_size;
		size_t m_capacity;
	};
}