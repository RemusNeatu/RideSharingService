// Copyright 2019 Neatu Remus-Mihai 

#include "./Driver.h"
#include <string>
#include <iomanip>
#include <fstream>

Driver::Driver(std::string name, std::string location) {
	this->name = name;
	this->location = location;
	this->distance = 0;
	this->rating = 0;
	this->nrRaces = 0;
	this->status = true;
}

Driver::~Driver() {
}

void Driver::newRace(std::string destination, int dist, int rating) {
	this->location = destination;
	this->distance += dist;
	++this->nrRaces;
	this->rating += rating;
}

void Driver::goOnline(const std::string &loc) {
	this->status = true;
	this->location = loc;
}

void Driver::goOffline() {
	this->status = false;
}

bool Driver::getStatus() {
	return this->status;
}

double Driver::getRating() const {
	if (this->nrRaces == 0) {
		return 0;
	}
	return (double)(this->rating / this->nrRaces);
}

int Driver::getDistance() {
	return this->distance;
}

int Driver::getNrRaces() {
	return this->nrRaces;
}

std::string Driver::getLocation() const {
	return this->location;
}

std::string Driver::getName() const {
	return this->name;
}

std::ostream& operator<< (std::ostream &fout, const Driver &driver) {
	std::string stat;
	if (driver.status) {
		stat = "online";
	} else {
		stat = "offline";
	}
	fout << std::fixed << driver.name <<": " << driver.location << ' ' <<
		    driver.getRating() << ' ' << driver.nrRaces
	     << ' ' << driver.distance << ' ' << stat;
	return fout;
}

bool Driver::operator>(const Driver &b) {
	if (this->getRating() > b.getRating()) {
		return 1;
	}
	if (this->getRating() == b.getRating()) {
		if (name < b.name) {
			return 1;
		}
	}
	return 0;
}

template<typename T>
ranking<T>::ranking(std::string name, T criteria) {
	this->name = name;
	this->criteria = criteria;
}

template<typename T>
ranking<T>::ranking() {
	this->name = "kk";
	this->criteria = -1;
}

template<typename T>
ranking<T>::ranking(const ranking &key) {
	this->name = key.name;
	this->criteria = key.criteria;
}

template<typename T>
ranking<T>::~ranking() {
}

template<typename T>
ranking<T>& ranking<T>::operator=(const ranking &key) {
	this->name = key.name;
	this->criteria = key.criteria;
	return *this;
}

template<typename T>
bool ranking<T>::operator<(const ranking &b) {
	if (this->criteria > b.criteria) {
		return 1;
	}
	if (this->criteria < b.criteria) {
		return 0;
	}
	return (this->name < b.name);
}

template<typename T>
const std::string& ranking<T>::getName() {
	return this->name;
}

template<typename T>
const T& ranking<T>::getCriteria() {
	return this->criteria;
}

template class ranking<int>;
template class ranking<double>;
