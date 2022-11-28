#pragma once
#include <functional>
#include <utility>
#include <initializer_list>
#include <type_traits>
#include "globals.h"


namespace Containers {
	template<
		typename K, typename V,
		typename Hash = std::hash<K>,
		typename Equal = std::equal_to<K>>
	class UnorderedMap {
	public:
		using KV = std::pair<const K, V>;
		using IRT = template<class IT, class NT> struct {
			IT position;
			bool inserted;
			NT node;
		};

		UnorderedMap() : UnordereMap(Global::UNORDERED_MAP_INIT_BUCKET_COUNT) {}

		explicit UnorderedMap(size_t, const Hash& =Hash(), const Equal=Equal());

		UnorderedMap(size_t bucket_count) :
			UnorderedMap(bucket_count, Hash(), Equal()) {}

		template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
		UnorderedMap(IT, IT, 
			size_t = Global::UNORDERED_MAP_INIT_BUCKET_COUNT, 
			const Hash & = Hash(), 
			const Equal = Equal());

		template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
		UnorderedMap(IT first, IT last, size_t bucket_count) :
			UnorderedMap(first, last, bucket_count, Hash(), Equal()) {}

		template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
		UnorderedMap(IT first, IT last, size_t bucket_count, const Hash& hash) :
			UnorderedMap(first, last, bucket_count, hash, Equal()) {}

		UnorderedMap(const UnorderedMap&);

		UnorderedMap(UnorderedMap&&) noexcept;

		UnorderedMap(std::initializer_list<KV>,
			size_t = Global::UNORDERED_MAP_INIT_BUCKET_COUNT,
			const Hash & = Hash(),
			const Equal = Equal());

		UnorderedMap(std::initializer_list<KV> il, size_t bucket_count) :
			UnorderedMap(il, bucket_count, Hash(), Equal()) {}

		UnorderedMap(std::initializer_list<KV> il, size_t bucket_count, const Hash& hash) :
			UnorderedMap(il, bucket_count, hash, Equal()) {}

		~UnorderedMap();

		UnorderedMap& operator=(const UnorderedMap&);
		
		UnorderedMap& operator=(UnorderedMap&&) noexcept;
		
		UnorderedMap& operator=(std::initializer_list<KV>);

		// Iterators
		class Iterator;

		Iterator begin() noexcept;

		const Iterator begin() const noexcept;

		Iterator end() noexcept;

		const Iterator end() const noexcept;

		// Capacity
		bool empty() const noexcept;

		size_t size() const noexcept;

		// Modifiers
		void clear() noexcept;

		std::pair<Iterator, bool> insert(const KV&);

		std::pair<Iterator, bool> insert(KV&&);

		std::pair<Iterator, bool> insert(const Iterator, const KV&);

		std::pair<Iterator, bool> insert(const Iterator, KV&&);

		template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
		void insert(IT, IT);

		void insert(std::initializer_list<KV>);

		IRT insert(MapNode&&);
		
		Iterator insert(const Iterator, MapNode&&);

		template <class M>
		std::pair<Iterator, bool> insert_or_assign(const K&, M&&);

		template <class M>
		std::pair<Iterator, bool> insert_or_assign(K&&, M&&);

		template <class M>
		Iterator insert_or_assign(const Iterator, const K&, M&&);

		template <class M>
		Iterator insert_or_assign(const Iterator, K&&, M&&);

		template<class...Args>
		std::pair<Iterator, bool> emplace(Args&&...);

		template<class...Args>
		std::pair<Iterator, bool> emplace_hint(const Iterator, Args&&...);

		template<class...Args>
		std::pair<Iterator, bool> try_emplace(const K&, Args&&...);

		template<class...Args>
		std::pair<Iterator, bool> try_emplace(K&&, Args&&...);

		template<class...Args>
		Iterator try_emplace(const Iterator, const K&, Args&&...);

		template<class...Args>
		Iterator try_emplace(const Iterator, K&&, Args&&...);

		Iterator erase(Iterator);

		Iterator erase(const Iterator);

		Iterator erase(const Iterator, const Iterator);

		size_t erase(const K&);

		template<class Q>
		size_t erase(Q&&);

		void swap(UnorderedMap&) noexcept;
			
		MapNode extract(const Iterator);
		
		MapNode extract(const K&);
		
		template<class Q>
		MapNode extract(Q&&);

		template<class H2, class E2>
		void merge(UnorderedMap<K, V, H2, E2>&);

		template<class H2, class E2>
		void merge(UnorderedMap<K, V, H2, E2>&&);

		template<class H2, class E2>
		void merge(UnorderedMultiMap<K, V, H2, E2>&);

		template<class H2, class E2>
		void merge(UnorderedMultiMap<K, V, H2, E2>&&);

		// Look-Up
		V& at(const K&);

		const V& at(const K&) const;

		V& operator[](const K&);

		V& operator[](K&&);

		size_t count(const K&) const;

		template<class Q>
		size_t count(const Q&) const;

		Iterator find(const K&);

		const Iterator find(const K&) const;

		template<class Q>
		Iterator find(const Q&);

		template<class Q>
		const Iterator find(const Q&) const;

		bool contains(const K&) const;

		template<class Q>
		bool contains(const Q&) const;

		std::pair<Iterator, Iterator> equal_range(const K&);

		std::pair<const Iterator, const Iterator> equal_range(const K&) const;

		template<class Q>
		std::pair<Iterator, Iterator> equal_range(const Q&);

		template<class Q>
		std::pair<const Iterator, const Iterator> equal_range(const Q&) const;

		// Hash Policy
		double load_factor() const;

		double max_load_factor() const;

		void max_load_factor(double);

		void rehash(size_t);

		void reserve(size_t);

		// Observers
		Hash hash_function() const;

		Equal key_eq() const;

	private:
		struct MapNode;
		MapNode* m_buckets;
		size_t m_size;
		size_t m_bucket_count;
		double m_max_load_factor;
	};

	template<
		typename K, typename V,
		typename Hash = std::hash<K>,
		typename Equal = std::equal_to<K>>
		class UnorderedMultiMap;

	template<
		typename K, typename V, 
		typename Hash, typename Equal>
	class UnorderedMap<K, V, Hash, Equal>::Iterator {
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
		KV* m_pointer;
	};

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	struct UnorderedMap<K, V, Hash, Equal>::MapNode {
		KV key_value;
		MapNode* prev;
		MapNode* next;
	};
}