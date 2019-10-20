// Copyright 2019 Neatu Remus-Mihai

#pragma once 

#include <string>

unsigned int hash_int(const int &key);
unsigned int hash_string(const std::string &key);

template<typename T>
unsigned int template_hash(const T &key);

template<>
unsigned int template_hash(const std::string &key);
