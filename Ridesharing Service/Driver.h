// Copyright 2019 Neatu Remus-Mihai 

#pragma once

#include <vector>
#include <string>

template<typename T>
class ranking {
 private:
	std::string name;
	T criteria;

 public:
	ranking(std::string name, T criteria);
	ranking();
	~ranking();
	ranking(const ranking &key);
	ranking<T>& operator=(const ranking &key);
	bool operator<(const ranking &b);
	const std::string& getName();
	const T& getCriteria();
};

class Driver {
 private:
	std::string name;
	std::string location;
	double rating;
	int nrRaces;
	int distance;
	bool status;

 public:
	Driver(std::string name, std::string location);
	~Driver();
	void newRace(std::string destination, int dist, int rating);
	friend std::ostream& operator<< (std::ostream &fout, const Driver &driver);
	void goOnline(const std::string &loc);
	void goOffline();
	bool getStatus();
	std::string getName() const;
	std::string getLocation() const;
	double getRating() const;
	int getDistance();
	int getNrRaces();
	bool operator>(const Driver &b);
};
