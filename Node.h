#pragma once
#include <iostream>
using namespace std;

template <typename K, typename V, typename F> class Dictionary;

//clasa pentru noduri
template <typename K, typename V>
class Node {
	K key;
	V value;
	char color;
	Node* left, * right, * parent;

public:
	Node(K&, V&);	

	friend class Dictionary<K, V, F>;
};

//constructor cu parametrii
template <typename K, typename V>
inline Node<K, V>::Node(K& k, V& v) : key(k), value(v), color('r'), left(NULL), right(NULL), parnt(NULL) {}
