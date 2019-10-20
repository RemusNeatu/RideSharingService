// Copyright 2019 Neatu Remus-Mihai

#pragma once

#include <list>
#include <vector>
#include <utility>

template<typename K, typename V>
class HashTable {
 public:
	typedef unsigned int (*HashFunc)(const K &key);

	explicit HashTable(HashFunc hash, int bucketSize = 100);
	~HashTable();
	void insert(const K &key, const V &val);
	void erase(const K &key);
	V& operator[](const K &key);
	const V& operator[](const K &key) const;
	bool find(const K &key) const;
 private:
	std::vector<std::list<std::pair<K, V> > > H;
	HashFunc hash;
};