// Copyright 2019 Neatu Remus-Mihai

#pragma once

#include <vector>
#include <string>
#include "HashTable.h"
#include "HashFunctions.h"

template<typename T>
class Graph {
 private:
	std::vector<std::vector<int> > neighbours;

 public:
	HashTable<T, int> toIndex;
	HashTable<int, T> toName;
	explicit Graph(std::vector<T> v);
	~Graph();
	void insertEdge(const T &source, const T& dest);
	void eraseEdge(const T &source, const T& dest);
	void reverseEdge(const T &source, const T& dest);
	int distance(const T &source, const T &dest);
	std::vector<std::vector<int> > distMatrix();
};

#endif
