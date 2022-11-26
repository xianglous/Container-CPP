#pragma once
#include <functional>
#include <utility>
#include <initializer_list>
#include "globals.h"


namespace Containers {
	template<
		typename K, typename V,
		typename Hash = std::hash<K>,
		typename Equal = std::equal_to<K>>
		class UnorderedMap {
		public:
			typedef typename std::pair<const K, V> value_type;

			UnorderedMap() : 
				m_size(0), m_bucket_count(UNORDERED_MAP_INIT_SIZE), 
				m_max_load_factor(UNORDERED_MAP_INIT_LOAD_FACTOR) {}

			UnorderedMap(std::initializer_list<value_type>);

			template<class IT>
			UnorderedMap(IT, IT);

			UnorderedMap(const UnorderedMap&);

			UnorderedMap(UnorderedMap&&);

			~UnorderedMap();

			size_t size() const;

			V& operator[](const K&);

			const V& operator[](const K&) const;


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
		value_type* m_buckets;
		size_t m_size;
		size_t m_bucket_count;
		double m_max_load_factor;
	};


}