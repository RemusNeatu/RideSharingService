// Copyright 2019 Neatu Remus-Mihai

#include "./HashFunctions.h"
#include <cmath>
#include <string>

unsigned int hash_int(const int &key) {
	return abs(key) & 0XFFFF;
}

//  Dan Bernstein hash function
unsigned int hash_string(const std::string &key) {
    unsigned int hash = 5381;

    for (auto x : key) {
        hash = ((hash << 5) + hash) + x;
    }

    return hash;
}

template<typename T>
unsigned int template_hash(const T &key) {
    unsigned int hash = 0;
    unsigned char* data = (unsigned char*) &key;

    for (int i = 0; i < sizeof(key); ++i) {
        hash = (hash << 5) + hash + data[i];
    }

    return hash;
}

//  Dan Bernstein hash function
template<>
unsigned int template_hash(const std::string &key) {
    unsigned int hash = 5381;

	for (auto x : key) {
		hash = ((hash << 5) + hash) + x;
	}

	return hash;
}
