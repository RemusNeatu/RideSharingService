// Copyright 2019 Neatu Remus-Mihai

#include "./Graph.h"
#include <string>
#include <vector>
#include <queue>

template<typename IteratorType, typename T>
IteratorType find(IteratorType begin,
							  IteratorType end, const T &elem) {
	auto it = begin;
	while (it != end) {
		if (*it == elem) {
			return it;
		}
		++it;
	}

	return end;
}

template<typename T>
Graph<T>::Graph(std::vector<T> v)
	: neighbours(v.size())
	, toIndex(template_hash)
	, toName(hash_int)

{
	int cnt = 0;
	for (auto x : v) {
		toIndex[x] = cnt;
		toName[cnt] = x;
		++cnt;
	}
}

template<typename T>
Graph<T>::~Graph() {
}

template<typename T>
void Graph<T>::insertEdge(const T &source, const T& dest) {
	if (source == dest) return;
	int A = toIndex[source];
	int B = toIndex[dest];
	if (find(neighbours[A].begin(), neighbours[A].end(), B) ==
										neighbours[A].end()) {
		neighbours[A].push_back(B);
	}
}

template<typename T>
void Graph<T>::eraseEdge(const T &source, const T& dest) {
	int A = toIndex[source];
	int B = toIndex[dest];
	auto it = find(neighbours[A].begin(), neighbours[A].end(), B);
	if (it != neighbours[A].end()) {
		neighbours[A].erase(it);
	}
}

template<typename T>
void Graph<T>::reverseEdge(const T &source, const T& dest) {
	int A = toIndex[source];
	int B = toIndex[dest];
	int okA = 0;
	int okB = 0;
	auto itB = find(neighbours[A].begin(), neighbours[A].end(), B);
	if (itB != neighbours[A].end()) {
		okB = 1;
	}

	auto itA = find(neighbours[B].begin(), neighbours[B].end(), A);
	if (itA != neighbours[B].end()) {
		okA = 1;
	}
	if (okA == okB) {
		return;
	}
	if (okA) {
		neighbours[B].erase(itA);
		neighbours[A].push_back(B);
	} else {
		neighbours[A].erase(itB);
		neighbours[B].push_back(A);
	}
}

template<typename T>
int Graph<T>::distance(const T &source, const T &dest) {
	std::queue<int> Q;
	std::vector<int> d;
	d.assign(neighbours.size(), -1);
	Q.push(toIndex[source]);
	d[toIndex[source]] = 0;

	while (!Q.empty()) {
		int aux = Q.front();
		Q.pop();
		for (auto x : neighbours[aux]) {
			if (d[x] > d[aux] + 1 || d[x] == -1) {
				d[x] = d[aux] + 1;
				Q.push(x);
			}
		}
	}

	return d[toIndex[dest]];
}

template<typename T>
std::vector<std::vector<int> > Graph<T>::distMatrix() {
	int n = neighbours.size();
	std::vector<std::vector<int> > d;
	d.resize(n);
	for (int i = 0; i < n; ++i) {
		d[i].assign(n, -1);
		d[i][i] = 0;
	}

	for (int i = 0; i < n; ++i) {
		std::queue<int> Q;
		Q.push(i);

		while (!Q.empty()) {
			int aux = Q.front();
			Q.pop();
			for (auto x : neighbours[aux]) {
				if (d[i][x] > d[i][aux] + 1 || d[i][x] == -1) {
					d[i][x] = d[i][aux] + 1;
					Q.push(x);
				}
			}
	}
	}

	return d;
}

template class Graph<std::string>;
