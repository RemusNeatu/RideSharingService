// Copyright 2019 Neatu Remus-Mihai

#include "./HashTable.h"
#include <utility>
#include <string>

template<typename K, typename V>
HashTable<K, V>::HashTable(HashFunc hash, int bucketSize) {
	this->hash = hash;
	H.resize(bucketSize);
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K &key, const V &val) {
	int b = hash(key) % H.size();

	auto it = H[b].begin();
	while (it != H[b].end()) {
		if (it->first == key) {
			it->second = val;
			return;
		}
		++it;
	}

	H[b].push_back({key, val});
}

template<typename K, typename V>
void HashTable<K, V>::erase(const K &key) {
	int b = hash(key) % H.size();

	auto it = H[b].begin();
	while (it != H[b].end()) {
		if (it->first == key) {
			H[b].erase(it);
			return;
		}
		++it;
	}
}

template<typename K, typename V>
V& HashTable<K, V>::operator[](const K &key) {
	int b = hash(key) % H.size();

	auto it = H[b].begin();
	while (it != H[b].end()) {
		if (it->first == key) {
			return it->second;
		}
		++it;
	}

	H[b].push_back({key, V()});
	return H[b].back().second;
}

template<typename K, typename V>
const V& HashTable<K, V>::operator[](const K &key) const {
	int b = hash(key) % H.size();

	auto it = H[b].begin();
	while (it != H[b].end()) {
		if (it->first == key) {
			return it->second;
		}
		++it;
	}
	// nu ar trebui sa se anunga aici
	return V();
}

template<typename K, typename V>
bool HashTable<K, V>::find(const K &key) const {
	int b = hash(key) % H.size();

	auto it = H[b].begin();
	while (it != H[b].end()) {
		if (it->first == key) {
			return true;
		}
		++it;
	}

	return false;
}

template class HashTable<std::string, int>;
template class HashTable<int, std::string>;
