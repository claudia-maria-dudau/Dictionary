#pragma once
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//clasa template KeyComp
template <typename K>
class KeyComp {
public:
	//supraincarcare operator () ce returneaza true daca
	//cheia 1 este mai mica decat cheia 2 sau false altfel
	bool operator () (const K& key1, const K& key2) const {
		if (key1 < key2)
			return true;
		else
			return false;
	}
};

//clasa specializata pentru stringuri KeyComp
template <>
class KeyComp<string> {
public:
	//compararea se face doar intre primele n/2 caractere
	//ale fiecarei chei (n = min lungimilor celor doua chei)
	bool operator () (const string& key1, const string& key2) const {
		int n = min(key1.length(), key2.length());
		n = n % 2 == 0 ? n / 2 : n / 2 + 1;
		if (key1.substr(0, n) > key2.substr(0, n))
			return true;
		else
			return false;
	}
};

