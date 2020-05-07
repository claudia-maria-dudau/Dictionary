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
	Dictionary(const Dictionary<K, V, F>&);
	~Dictionary();
	void push(const K&, const V&);
	void pop(const K&);
	const bool search(const K&) const;
	void clear();

	V operator [] (const K&) const;
	void operator =(const Dictionary<K, V, F>&);

	friend ostream& operator << (ostream&, const Dictionary&) const;
};

//constructor fara parametrii
template <typename K, typename V, typename F>
inline Dictionary<K, V, F>::Dictionary() : start(NULL){}

//constructor de copiere
template<typename K, typename V, typename F>
inline Dictionary<K, V, F>::Dictionary(const Dictionary<K, V, F>& D) {
	*this = D;
}

//destructor
template<typename K, typename V, typename F>
inline Dictionary<K, V, F>::~Dictionary() {
	this->clear();
}

//operator de atribuire
template<typename K, typename V, typename F>
inline void Dictionary<K, V, F>::operator =(const Dictionary<K, V, F>& D) {
	if (this != D) {
		this->~Dictionary();
		deque<Node<K, V>*> q;
		q.push_back(D.start);
		while (q) {
			if (q.front->left != NULL)
				q.push_back(q.front->left);
			if (q.front->right != NULL)
				q.push_back(q.front->right);
			this->push(q.front->key, q.front->value);
			q.pop_front();
		}
	}
}

