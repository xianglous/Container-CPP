#pragma once
#include <functional>
#include <initializer_list>
#include <type_traits>
#include <utility>
#include "linked_list.h"
#include "globals.h"


namespace Containers {
	template<
		typename K, typename V,
		typename Hash = std::hash<K>,
		typename Equal = std::equal_to<K>>
	class UnorderedMap {
	private:
		struct MapNode;
	public:
		//class Iterator;
		using KV = std::pair<const K, V>;
		using IRT = struct {
			Iterator position;
			bool inserted;
			MapNode node;
		};
		using LL = std::pair<MapNode*, MapNode*>;

		class Iterator;

		UnorderedMap() : UnordereMap(Global::UNORDERED_MAP_INIT_BUCKET_COUNT) {}

		explicit UnorderedMap(size_t, const Hash& =Hash(), const Equal& =Equal());

		UnorderedMap(size_t bucket_count) :
			UnorderedMap(bucket_count, Hash(), Equal()) {}

		template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
		UnorderedMap(IT, IT, 
			size_t = Global::UNORDERED_MAP_INIT_BUCKET_COUNT, 
			const Hash& = Hash(), 
			const Equal& = Equal());

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
			const Hash& = Hash(),
			const Equal& = Equal());

		UnorderedMap(std::initializer_list<KV> il, size_t bucket_count) :
			UnorderedMap(il, bucket_count, Hash(), Equal()) {}

		UnorderedMap(std::initializer_list<KV> il, size_t bucket_count, const Hash& hash) :
			UnorderedMap(il, bucket_count, hash, Equal()) {}

		~UnorderedMap();

		UnorderedMap& operator=(const UnorderedMap&);
		
		UnorderedMap& operator=(UnorderedMap&&) noexcept;
		
		UnorderedMap& operator=(std::initializer_list<KV>);

		// Iterators

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

		template<class P, std::enable_if_t<std::is_constructible<KV, P&&>::value>...>
		std::pair<Iterator, bool> insert(P&&);

		Iterator insert(const Iterator, const KV&);

		Iterator insert(const Iterator, KV&&);

		template<class P, std::enable_if_t<std::is_constructible<KV, P&&>::value>...>
		Iterator insert(const Iterator, P&&);

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

		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
		size_t erase(Q&&);

		void swap(UnorderedMap&) noexcept;
			
		MapNode extract(const Iterator);
		
		MapNode extract(const K&);
		
		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
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

		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
		size_t count(const Q&) const;

		Iterator find(const K&);

		const Iterator find(const K&) const;

		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
		Iterator find(const Q&);

		template<class Q, std::enable_if_t<Hash::is_transparent&&Equal::is_transparent>...>
		const Iterator find(const Q&) const;

		bool contains(const K&) const;

		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
		bool contains(const Q&) const;

		std::pair<Iterator, Iterator> m_equal_range(const K&);

		std::pair<const Iterator, const Iterator> m_equal_range(const K&) const;

		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
		std::pair<Iterator, Iterator> m_equal_range(const Q&);

		template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
		std::pair<const Iterator, const Iterator> m_equal_range(const Q&) const;

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
		//struct MapNode;
		LL* m_buckets;
		size_t m_bucket_count;
		size_t m_size;
		size_t m_begin_index;
		double m_max_load_factor;
		const Hash& m_hasher;
		const Equal& m_equal;

		void allocate(size_t bucket_count);

		size_t hash(const K&) const;

		void insert_between(size_t, MapNode*, MapNode*, MapNode*);

		Iterator erase(size_t, MapNode*);
	};

	template<
		typename K, typename V,
		typename Hash = std::hash<K>,
		typename Equal = std::equal_to<K>>
	class UnorderedMultiMap {

	};

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	class UnorderedMap<K, V, Hash, Equal>::Iterator {
	public:
		Iterator() : m_pointer(nullptr) {}

		Iterator(ListNode* pointer) : m_pointer(pointer) {}

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

		KV& operator*();

		const KV& operator*() const;

		KV* operator->();

		const KV* operator->() const;
	private:
		friend class UnorderedMap;
		MapNode* m_pointer;
	};

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	struct UnorderedMap<K, V, Hash, Equal>::MapNode {
		KV key_value;
		MapNode* prev;
		MapNode* next;
		MapNode() : key_value(), prev(nullptr), next(nullptr) {}
		MapNode(const KV& kv) : 
			key_value(kv), prev(nullptr), next(nullptr) {}
		MapNode(T&& kv) :
			key_value(std::move(kv)), prev(nullptr), next(nullptr) {}
	};


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::UnorderedMap(
		size_t bucket_count,
		const Hash& m_hasher,
		const Equal& m_equal) :
		m_size(),
		m_max_load_factor(Global::UNORDERED_MAP_INIT_LOAD_FACTOR),
		m_hasher(m_hasher), m_equal(m_equal) {
		allocate(bucket_count);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
	UnorderedMap<K, V, Hash, Equal>::UnorderedMap(
		IT first, IT last,
		size_t bucket_count,
		const Hash& m_hasher,
		const Equal& m_equal) :
		m_size(),
		m_max_load_factor(Global::UNORDERED_MAP_INIT_LOAD_FACTOR),
		m_hasher(m_hasher), m_equal(m_equal) {
		allocate(bucket_count);
		insert(first, last);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::UnorderedMap(const UnorderedMap& other) :,
		m_size(other.m_size),
		m_hasher(other.m_hasher), m_equal(other.m_equal) {
		allocate(other.m_bucket_count);
		insert(other.begin(), other.end());
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::UnorderedMap(UnorderedMap&&) noexcept : 
		m_buckets(std::move(other.m_buckets)),
		m_bucket_count(std::move(other.m_bucket_count)),
		m_size(std::move(other.m_size)),
		m_hasher(std::move(other.m_hasher)),
		m_equal(std::move(other.m_equal)) {}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::UnorderedMap(std::initializer_list<KV> il,
		size_t bucket_count,
		const Hash& m_hasher,
		const Equal& m_equal) :
		m_size(), m_hasher(m_hasher), m_equal(m_equal) {
		allocate(bucket_count);
		insert(il);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::~UnorderedMap() {
		erase(begin(), end());
		delete[] m_buckets;
		m_bucket_count = 0;
		m_size = 0;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>& UnorderedMap<K, V, Hash, Equal>::operator=(const UnorderedMap& other) {
		UnorderedMap<K, V, Hash, Equal> temp(other);
		temp.swap(*this);
		return *this;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>& UnorderedMap<K, V, Hash, Equal>::operator=(UnorderedMap&& other) noexcept {
		other.swap(*this);
		return *this;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>& UnorderedMap<K, V, Hash, Equal>::operator=(std::initializer_list<KV> il) {
		UnorderedMap<K, V, Hash, Equal> temp(il);
		temp.swap(*this);
		return *this;
	}

	// Iterators
	template<
		typename K, typename V,
		typename Hash, typename Equal>
	bool UnorderedMap<K, V, Hash, Equal>::Iterator::operator==(const Iterator& other) const {
		return m_pointer == other.m_pointer;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	bool UnorderedMap<K, V, Hash, Equal>::Iterator::operator!=(const Iterator& other) const {
		return m_pointer != other.m_pointer;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator& UnorderedMap<K, V, Hash, Equal>::Iterator::operator++() {
		if (!m_pointer->next) throw OutOfRangeException("LinkedList");
		m_pointer = m_pointer->next;
		return *this;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::Iterator::operator++(int) {
		Iterator it = *this;
		++(*this);
		return it;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::Iterator::operator+(int steps) const {
		Iterator it = *this;
		for (int i = 0; i < steps; ++i, ++it);
		return it;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator& UnorderedMap<K, V, Hash, Equal>::Iterator::operator+=(int steps) {
		*this = *this + steps;
		return *this;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator& UnorderedMap<K, V, Hash, Equal>::Iterator::operator--() {
		if (!m_pointer->prev) throw OutOfRangeException("LinkedList");
		m_pointer = m_pointer->prev;
		return *this;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::Iterator::operator--(int) {
		Iterator it = *this;
		--(*this);
		return it;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::Iterator::operator-(int steps) const {
		Iterator it = *this;
		for (int i = 0; i < steps; ++i, --it);
		return it;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator& UnorderedMap<K, V, Hash, Equal>::Iterator::operator-=(int steps) {
		*this = *this - steps;
		return *this;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	size_t UnorderedMap<K, V, Hash, Equal>::Iterator::operator-(const Iterator& other) const {
		size_t dis = 0;
		for (Iterator it = other; it.m_pointer; ++it, ++dis) {
			if (m_pointer == it.m_pointer) return dis;
		}
		throw InvalidIteratorException("LinkedList");
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::KV& UnorderedMap<K, V, Hash, Equal>::Iterator::operator*() {
		return m_pointer->value;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	const UnorderedMap<K, V, Hash, Equal>::KV& UnorderedMap<K, V, Hash, Equal>::Iterator::operator*() const {
		return m_pointer->value;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	UnorderedMap<K, V, Hash, Equal>::KV* UnorderedMap<K, V, Hash, Equal>::Iterator::operator->() {
		return &(m_pointer->value);
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	const UnorderedMap<K, V, Hash, Equal>::KV* UnorderedMap<K, V, Hash, Equal>::Iterator::operator->() const {
		return &(m_pointer->value);
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::begin() noexcept {
		return Iterator(std::get<0>(m_buckets[m_begin_index]))
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	const typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::begin() const noexcept {
		return Iterator(std::get<0>(m_buckets[m_begin_index]))
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::end() noexcept {
		return Iterator(std::get<1>(m_buckets[m_bucket_count]))
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	const typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::end() const noexcept {
		return Iterator(std::get<1>(m_buckets[m_bucket_count]))
	}

	// Capacity
	template<
		typename K, typename V,
		typename Hash, typename Equal>
	bool UnorderedMap<K, V, Hash, Equal>::empty() const noexcept { return m_size; }


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	size_t UnorderedMap<K, V, Hash, Equal>::size() const noexcept { return m_size; }

	// Modifiers
	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::clear() noexcept {
		erase(begin(), end());
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::insert(const KV& key_value) {
		if (load_factor() >= m_max_load_factor)
			rehash(m_bucket_count * Global::UNORDERED_MAP_RESIZE_FACTOR);
		MapNode* new_node = new MapNode(key_value);
		const auto& [key, val] = key_value;
		Iterator pos = find(key);
		if (pos != end()) {
			delete new_node;
			return { pos, false };
		}
		size_t bucket = hash(key);
		auto [head, tail] = m_buckets[bucket];
		insert_between(bucket, new_node, tail, tail->next);
		return { Iterator(new_node), true };
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::insert(KV&& key_value) {
		return emplace(std::forward<KV>(key_value));
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class P, std::enable_if_t<std::is_constructible<std::pair<const K, V>, P&&>::value>...>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::insert(P&& key_value) {
		return emplace(std::forward<P>(key_value));
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::insert(const Iterator pos, const KV& key_value) {
		if (m_equal(pos->first, std::get<0>(key_value)))
			return { pos, false };
		return insert(key_value);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::insert(const Iterator pos, KV&& key_value) {
		return emplace_hint(pos, std::forward<KV>(key_value));
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class P, std::enable_if_t<std::is_constructible<std::pair<const K, V>, P&&>::value>...>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::insert(const Iterator pos, P&& key_value) {
		return emplace_hint(pos, std::forward<P>(key_value));
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class IT, std::enable_if_t<!std::is_integral<IT>::value>...>
	void UnorderedMap<K, V, Hash, Equal>::insert(IT first, IT last) {
		for (IT it = first; it != last; ++it) {
			insert(*it);
		}
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::insert(std::initializer_list<KV> il) {
		return insert(il.begin(), il.end());
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::IRT UnorderedMap<K, V, Hash, Equal>::insert(MapNode&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::insert(const Iterator, MapNode&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template <class M>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::insert_or_assign(const K&, M&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template <class M>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::insert_or_assign(K&&, M&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template <class M>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::insert_or_assign(const Iterator, const K&, M&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template <class M>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::insert_or_assign(const Iterator, K&&, M&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class...Args>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::emplace(Args&&...args) {
		if (load_factor() >= m_max_load_factor)
			rehash(m_bucket_count * Global::UNORDERED_MAP_RESIZE_FACTOR);
		MapNode* new_node = new MapNode(std::forward<Args>(args)...);
		const auto& [key, val] = new_node->key_value;
		Iterator pos = find(key);
		if (pos != end()) {
			delete new_node;
			return { pos, false };
		}
		size_t bucket = hash(key);
		auto [head, tail] = m_buckets[bucket];
		insert_between(bucket, new_node, tail, tail->next);
		return { Iterator(new_node), true };
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class...Args>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::emplace_hint(const Iterator pos, Args&&...args) {
		return emplace(std::forward<Args>(args)...);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class...Args>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::try_emplace(const K&, Args&&...);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class...Args>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, bool> UnorderedMap<K, V, Hash, Equal>::try_emplace(K&&, Args&&...);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class...Args>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::try_emplace(const Iterator, const K&, Args&&...);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class...Args>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::try_emplace(const Iterator, K&&, Args&&...);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::erase(Iterator pos) {
		if (!pos.m_pointer) throw InvalidIteratorException("UnorderedMap");
		size_t bucket = hash(pos->first);
		return erase(bucket, pos.m_pointer); 
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::erase(const Iterator pos) {
		if (!pos.m_pointer) throw InvalidIteratorException("UnorderedMap");
		size_t bucket = hash(pos->first);
		return erase(bucket, pos.m_pointer);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::erase(const Iterator first, const Iterator last) {
		Iterator out = first;
		for (Iterator it = first; it != last; ++it) {
			out = erase(it);
		}
		return out;
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	size_t UnorderedMap<K, V, Hash, Equal>::erase(const K& key) {
		if (!contains(key)) return 0;
		erase(find(key));
		return 1;
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	size_t UnorderedMap<K, V, Hash, Equal>::erase(Q&& query) {
		if (!contains(std::move(query))) return 0;
		erase(find(std::move(query)));
		return 1;
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::swap(UnorderedMap& other) noexcept {
		std::swap(m_buckets, other.m_buckets);
		std::swap(m_bucket_count, other.m_bucket_count);
		std::swap(m_size, other.m_size);
		std::swap(m_hasher, other.m_hasher);
		std::swap(m_equal, other.m_equal);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::MapNode UnorderedMap<K, V, Hash, Equal>::extract(const Iterator);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::MapNode UnorderedMap<K, V, Hash, Equal>::extract(const K&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	typename UnorderedMap<K, V, Hash, Equal>::MapNode UnorderedMap<K, V, Hash, Equal>::extract(Q&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class H2, class E2>
	void UnorderedMap<K, V, Hash, Equal>::merge(UnorderedMap<K, V, H2, E2>&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class H2, class E2>
	void UnorderedMap<K, V, Hash, Equal>::merge(UnorderedMap<K, V, H2, E2>&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class H2, class E2>
	void UnorderedMap<K, V, Hash, Equal>::merge(UnorderedMultiMap<K, V, H2, E2>&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class H2, class E2>
	void UnorderedMap<K, V, Hash, Equal>::merge(UnorderedMultiMap<K, V, H2, E2>&&);

	// Look-Up

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	V& UnorderedMap<K, V, Hash, Equal>::at(const K&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	const V& UnorderedMap<K, V, Hash, Equal>::at(const K&) const;


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	V& UnorderedMap<K, V, Hash, Equal>::operator[](const K&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	V& UnorderedMap<K, V, Hash, Equal>::operator[](K&&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	size_t UnorderedMap<K, V, Hash, Equal>::count(const K&) const;


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	size_t UnorderedMap<K, V, Hash, Equal>::count(const Q&) const;


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::find(const K& key) {
		size_t bucket = hash(key);
		auto [head, tail] = m_buckets[bucket];
		return std::find_if(
			Iterator(head), Iterator(tail ? tail->next : nullptr),
			[this](const KV& key_value) {
				m_equal(std::get<0>(key_value), key);
			});
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	const typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::find(const K& key) const {
		size_t bucket = hash(key);
		auto [head, tail] = m_buckets[bucket];
		return std::find_if(
			Iterator(head), Iterator(tail ? tail->next : nullptr),
			[this](const KV& key_value) {
				m_equal(std::get<0>(key_value), key);
			});
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::find(const Q& query) {
		size_t bucket = hash(query);
		auto [head, tail] = m_buckets[bucket];
		return std::find_if(
			Iterator(head), Iterator(tail ? tail->next : nullptr),
			[this](const KV& key_value) {
				m_equal(std::get<0>(key_value), query);
			});
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	const typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::find(const Q& query) const {
		size_t bucket = hash(query);
		auto [head, tail] = m_buckets[bucket];
		return std::find_if(
			Iterator(head), Iterator(tail ? tail->next : nullptr),
			[this](const KV& key_value) {
				m_equal(std::get<0>(key_value), query);
			});
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	bool UnorderedMap<K, V, Hash, Equal>::contains(const K& key) const {
		return find(key) != end();
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	bool UnorderedMap<K, V, Hash, Equal>::contains(const Q& query) const {
		return find(query) != end();
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, typename UnorderedMap<K, V, Hash, Equal>::Iterator> UnorderedMap<K, V, Hash, Equal>::m_equal_range(const K&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	std::pair<const typename UnorderedMap<K, V, Hash, Equal>::Iterator, const typename UnorderedMap<K, V, Hash, Equal>::Iterator> UnorderedMap<K, V, Hash, Equal>::m_equal_range(const K&) const;


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	std::pair<typename UnorderedMap<K, V, Hash, Equal>::Iterator, typename UnorderedMap<K, V, Hash, Equal>::Iterator> UnorderedMap<K, V, Hash, Equal>::m_equal_range(const Q&);


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	template<class Q, std::enable_if_t<Hash::is_transparent&& Equal::is_transparent>...>
	std::pair<const typename UnorderedMap<K, V, Hash, Equal>::Iterator, const typename UnorderedMap<K, V, Hash, Equal>::Iterator> UnorderedMap<K, V, Hash, Equal>::m_equal_range(const Q&) const;

	// Hash Policy

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	double UnorderedMap<K, V, Hash, Equal>::load_factor() const {
		return m_size / m_bucket_count;
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	double UnorderedMap<K, V, Hash, Equal>::max_load_factor() const {
		return m_max_load_factor;
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::max_load_factor(double max_load_factor) {
		if (max_load_factor <= 0) throw std::exception("Invalid Load Factor");
		m_max_load_factor = max_load_factor;
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::rehash(size_t bucket_count) {
		UnorderedMap<K, V, Hash, Equal> temp(begin(), end(), bucket_count, m_hasher, m_equal);
		temp.swap(*this);
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::reserve(size_t) {
		rehash(ceil(m_size / m_max_load_factor));
	}

	// Observers

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	Hash UnorderedMap<K, V, Hash, Equal>::hash_function() const {
		return m_hasher
	}


	template<
		typename K, typename V,
		typename Hash, typename Equal>
	Equal UnorderedMap<K, V, Hash, Equal>::key_eq() const {
		return m_equal;
	}

	// Private Members
	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::allocate(size_t bucket_count) {
		m_buckets = new LL[bucket_count + 1];
		m_bucket_count = bucket_count;
		MapNode* tail = new MapNode();
		m_buckets[bucket_count] = LL(tail, tail);
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	size_t UnorderedMap<K, V, Hash, Equal>::hash(const K& key) const {
		return m_hasher(key) % m_bucket_count;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	void UnorderedMap<K, V, Hash, Equal>::insert_between(
		size_t bucket, 
		MapNode* new_node, 
		MapNode* prev, 
		MapNode* next) {
		new_node->prev = prev;
		new_node->next = next;
		auto &[head, tail] = m_buckets[bucket];
		if (prev) prev->next = new_node;
		if (!prev || next == head) head = new_node;
		if (next) next->prev = new_node;
		if (!next || prev == tail) tail = new_node;
		++m_size;
	}

	template<
		typename K, typename V,
		typename Hash, typename Equal>
	typename UnorderedMap<K, V, Hash, Equal>::Iterator UnorderedMap<K, V, Hash, Equal>::erase(size_t bucket, MapNode* node) {
		if (!node) throw OutOfRangeException("UnorderedMap");
		auto& [head, tail] = m_buckets[bucket];
		if (node->prev)
			node->prev->next = node->next;
		if (node == head) {
			head = node->next;
			head->prev = node->prev;
		}
		if (node->next)
			node->next->prev = node->prev;
		if (node == tail) {
			tail = node->prev;
			tail->next = node->next;
		}
		MapNode* next = node->next;
		delete node;
		--m_size;
		return Iterator(next);
	}

}