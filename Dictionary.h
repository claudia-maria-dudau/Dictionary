#pragma once
#include "Node.h"
#include "KeyComp.h"
#include <deque>
#include <exception>

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
	Node<K, V>* search(const K&) const;
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
Dictionary<K, V, F>::~Dictionary() {
	this->clear();
}

//metoda de cautare in arbore dupa o anumita cheie ce intoarce
//nodul ce contine cheia respectiva, sau NULL daca aceasta nu exista
template<typename K, typename V, typename F>
Node<K, V>* Dictionary<K, V, F>::search(const K& k) const {
	Node<K, V>* p = this->start;
	while (p) {
		//daca cheile sunt egale
		if (!cmp(p->key, k) && !cmp(k, p->key))
			return p;

		//daca cheia data este mai mica decat cea a nodului curent
		else if (cmp(k, p->key))
			p = p->left;

		//daca cheia data este mai mare decat cea a nodului curent
		else
			p = p->right;
	}
	return NULL;
}

//operator []pentru obtinerea valorii asociate unei chei date
template<typename K, typename V, typename F>
V Dictionary<K, V, F>::operator[](const K& k) const {
	//verific daca exista cheia in dictionar
	Node<K, V>* p;
	if (p = this->search(k))
		return p->value;
	
	//daca cheia nu exista in dictionar, arunc o eroare
	throw invalid_argument("cheia nu exista in dictionar");
}

//operator de atribuire
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::operator =(const Dictionary<K, V, F>& D) {
	//daca elementul curent este diferit de cel primit
	if (this != D) {
		//sterg elementul curent
		this->~Dictionary();

		//parcurg dictionarul primit (bfs) si adaug fiecare 
		//pereche (key, value) in obiectul curent
		deque<Node<K, V>*> q;
		q.push_back(D.start);
		while (q) {
			//daca nodul curent are fiu stang il adaug in coada
			if (q.front->left != NULL)
				q.push_back(q.front->left);

			//daca nodul curent are fiu drept il adaug in coada
			if (q.front->right != NULL)
				q.push_back(q.front->right);

			//adaug nodul curent in dictionar
			this->push(q.front->key, q.front->value);
			q.pop_front();
		}
	}
}

