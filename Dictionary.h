#pragma once
#include "Node.h"
#include "KeyComp.h"
#include <deque>

//clasa dictionar
template <typename K, typename V, typename F = KeyComp<K>>
class Dictionary {
	Node<K, V>* start;
	KeyComp cmp;

public:
	Dictionary();
	Dictionary(Dictionary<K, V, F>&);
};

//constructor fara parametrii
template <typename K, typename V, typename F>
inline Dictionary<K, V, F>::Dictionary() : start(NULL){}

//constructor de copiere
template<typename K, typename V, typename F>
inline Dictionary<K, V, F>::Dictionary(Dictionary<K, V, F>& D) {
	*this = D;
}





