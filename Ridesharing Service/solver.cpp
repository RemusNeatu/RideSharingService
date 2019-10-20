// Copyright 2019 Neatu Remus-Mihai

#include <string>
#include <vector>
#include <cassert>
#include <iomanip>
#include "./solver.h"
#include "./Graph.h"
#include "./Driver.h"

void solver::task1_solver(std::ifstream& fin, std::ofstream& fout) {
	fin.clear();
	fin.seekg(0, std::ios::beg);

	int n, m;
	fin >> n >> m;
	std::vector<std::string> v;
	std::string s;
	for (int i = 0; i < n; ++i) {
		fin >> s;
		v.push_back(s);
	}

	Graph<std::string> G(v);
	std::string src, dst;
	for (int i = 0; i < m; ++i) {
		fin >> src >> dst;
		G.insertEdge(src, dst);
	}

	int queries;
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
		if (G.distance(src, dst) == -1) {
			fout << "n\n";
		} else {
			fout << "y\n";
		}
	}
}

void solver::task2_solver(std::ifstream& fin, std::ofstream& fout) {
	fin.clear();
	fin.seekg(0, std::ios::beg);

	int n, m;
	fin >> n >> m;

	std::vector<std::string> v;
	std::string s;
	for (int i = 0; i < n; ++i) {
		fin >> s;
		v.push_back(s);
	}

	Graph<std::string> G(v);
	std::string src, dst;
	for (int i = 0; i < m; ++i) {
		fin >> src >> dst;
		G.insertEdge(src, dst);
	}

	int queries;
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
	}
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
		fout << G.distance(src, dst) << '\n';
	}
}

void solver::task3_solver(std::ifstream& fin, std::ofstream& fout) {
	fin.clear();
	fin.seekg(0, std::ios::beg);

	int n, m;
	fin >> n >> m;

	std::vector<std::string> v;
	std::string s;
	for (int i = 0; i < n; ++i) {
		fin >> s;
		v.push_back(s);
	}

	Graph<std::string> G(v);
	std::string src, dst;
	for (int i = 0; i < m; ++i) {
		fin >> src >> dst;
		G.insertEdge(src, dst);
	}

	int queries;
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
	}
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
	}
	fin >> queries;
	char c;
	int type;
	std::string aux;
	for (int i = 0; i < queries; ++i) {
		fin >> c >> src >> dst >> type;
		if (c == 'q') {
			switch(type) {
				case 0:
					if (G.distance(src, dst) == -1) {
						fout << "n\n";
					} else {
						fout << "y\n";
					}
					break;
				case 1:
					fout << G.distance(src, dst) << '\n';
					break;
				case 2:
					fin >> aux;
					if (G.distance(src, aux) == -1 || G.distance(aux, dst) == -1) {
						fout << -1 << '\n';
					} else {
						fout << G.distance(src, aux) + G.distance(aux, dst) << '\n';
					}
					break;
				default:
					break;
			}
		} else {
			switch(type) {
				case 0:
					G.insertEdge(src, dst);
					break;
				case 1:
					G.eraseEdge(src, dst);
					G.eraseEdge(dst, src);
					break;
				case 2:
					G.insertEdge(src, dst);
					G.insertEdge(dst, src);
					break;
				case 3:
					G.reverseEdge(src, dst);
					break;
				default:
					break;
			}
		}
	}
}

template <typename T>
void mergeSort(std::vector<T>& v, int begin, int end) {
	if (begin >= end) {
		return;
	}

	int mid = (begin + end) / 2;
	mergeSort(v, begin, mid);
	mergeSort(v, mid + 1, end);

	std::vector<T> tmp(end - begin + 1);
	int pos = 0;
	int i = begin, j = mid + 1;
	while (i <= mid && j <= end) {
		if (v[i] < v[j]) {
			tmp[pos++] = v[i++];
		} else {
			tmp[pos++] = v[j++];
		}
	}
	if (i <= mid) {
		while (i <= mid) {
			tmp[pos++] = v[i++];
		}
	}
	if (j <= end) {
		while (j <= end) {
			tmp[pos++] = v[j++];
		}
	}

	for (int k = 0; k < (int)tmp.size(); ++k) {
		v[begin + k] = tmp[k];
	}
}

void uberSimulator(std::ifstream& fin, std::ofstream& fout,
					Graph<std::string> &G) {
	fout.precision(3);

	int queries, rating, top, nrDrivers = 0;
	std::string command, name, start, finish;
	std::vector<Driver> D;
	std::vector<std::vector<int> > dist;
	dist = G.distMatrix();
	HashTable<std::string, int> drivers(template_hash);

	fin >> queries;
	for (int step = 0; step < queries; ++step) {
		fin >> command;
		switch (command[0]) {
			case 'd': {
				fin >> name >> start;
				if (!drivers.find(name)) {
					D.push_back(Driver(name, start));
					drivers[name] = nrDrivers++;

				} else {
					D[drivers[name]].goOnline(start);
				}
				break;
			}
			case 'b': {
				fin >> name;
				D[drivers[name]].goOffline();
				break;
			}
			case 'r': {
				fin >> start >> finish >> rating;
				int minn = 99999999;
				int closest = -1;
				int A, B;
				B = G.toIndex[start];
				for (int i = 0; i < nrDrivers; ++i) {
					if (D[i].getStatus()) {
						A = G.toIndex[D[i].getLocation()];
						if (dist[A][B] != -1 && dist[A][B] < minn) {
							minn = dist[A][B];
							closest = i;
						} else if (dist[A][B] == minn) {
							if (D[i].getRating() > D[closest].getRating()) {
								closest = i;
							}
						}
					}
				}

				A = B;
				int destination = G.toIndex[finish];
				if (dist[A][destination] == -1) {
					int ok = 0;
					for (int i = 0; i < (int)dist.size(); ++i) {
						if (dist[destination][i] == 1 && dist[A][i] != -1) {
							destination = i;
							ok = 1;
							break;
						}
					}
					if (!ok) {
						destination = -1;
					}
				}

				if (closest == -1) {
					fout << "Soferi indisponibili\n";
				} else if (destination == -1) {
					fout << "Destinatie inaccesibila\n";
				} else {
					D[closest].newRace(G.toName[destination],
						minn + dist[A][destination], rating);
				}

				break;
			}
			case 't': {
				fin >> top;
				if (top > nrDrivers) {
					top = nrDrivers;
				}
				switch (command[6]) {
					case 't': {
						std::vector<ranking<double> > R;
						for (int i = 0; i < nrDrivers; ++i) {
							R.push_back(ranking<double>(D[i].getName(), D[i].getRating()));
						}
						mergeSort(R, 0, R.size() - 1);
						for (int i = 0; i < top; ++i) {
							fout <<std::fixed<< R[i].getName() << ":" << R[i].getCriteria() << ' ';
						}
						fout << '\n';
						break;
					}
					case 's': {
						std::vector<ranking<int> > R;
						for (int i = 0; i < nrDrivers; ++i) {
							R.push_back(ranking<int>(D[i].getName(), D[i].getDistance()));
						}
						mergeSort(R, 0, R.size() - 1);
						for (int i = 0; i < top; ++i) {
							fout << R[i].getName() << ":" << R[i].getCriteria() << ' ';
						}
						fout << '\n';
						break;
					}
					case 'd': {
						std::vector<ranking<int> > R;
						for (int i = 0; i < nrDrivers; ++i) {
							R.push_back(ranking<int>(D[i].getName(), D[i].getNrRaces()));
						}
						mergeSort(R, 0, R.size() - 1);
						for (int i = 0; i < top; ++i) {
							fout << R[i].getName() << ":" << R[i].getCriteria() << ' ';
						}
						fout << '\n';
						break;
					}
				}

				break;
			}
			case 'i': {
				fin >> name;
				fout << D[drivers[name]] << '\n';
				break;
			}
			default:
				break;
		}
	}
}

void solver::task4_solver(std::ifstream& fin, std::ofstream& fout) {
	fin.clear();
	fin.seekg(0, std::ios::beg);

	int n, m;
	fin >> n >> m;

	std::vector<std::string> v;
	std::string s;
	for (int i = 0; i < n; ++i) {
		fin >> s;
		v.push_back(s);
	}

	Graph<std::string> G(v);
	std::string src, dst;
	for (int i = 0; i < m; ++i) {
		fin >> src >> dst;
		G.insertEdge(src, dst);
	}

	int queries;
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
	}
	fin >> queries;
	for (int i = 0; i < queries; ++i) {
		fin >> src >> dst;
	}

	fin >> queries;
	char c;
	int type;
	std::string aux;
	for (int i = 0; i < queries; ++i) {
		fin >> c >> src >> dst >> type;
		if (c == 'c') {
			switch(type) {
				case 0:
					G.insertEdge(src, dst);
					break;
				case 1:
					G.eraseEdge(src, dst);
					G.eraseEdge(dst, src);
					break;
				case 2:
					G.insertEdge(src, dst);
					G.insertEdge(dst, src);
					break;
				case 3:
					G.reverseEdge(src, dst);
					break;
			}
		} else {
			switch(type) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					fin >> aux;
					break;
				default:
					break;
			}
		}
	}

	uberSimulator(fin, fout, G);
}

void solver::task5_solver(std::ifstream& , std::ofstream&) {
}
