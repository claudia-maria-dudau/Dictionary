#pragma once
#include "Node.h"
#include "KeyComp.h"
#include <deque>
#include <exception>

//clasa dictionar
template <typename K, typename V, typename F = KeyComp<K>>
class Dictionary {
	Node<K, V>* root;
	KeyComp cmp;

protected:
	void rotate_left(Node<K, V>&);
	void rotate_right(Node<K, V>&);

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

	template <typename K, typename V, typename F>
	friend ostream& operator << (ostream&, const Dictionary<K, V, F>&);
};

//rotire nod la stanga in arbore
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::rotate_left(Node<K, V>& nod) {
	//daca este fiu stang
	if (nod == nod->parent->left) {
		//legatura parinte cu fiu drept
		nod->parent->left = nod->right;
		nod->right->parent = nod->parent;
	}

	//daca este fiu drept
	else {
		//legatura parinte cu fiu drept
		nod->parent->right = nod->right;
		nod->right->parent = nod->parent;
	}
		
	//legatura nod cu noul parinte (fiul drept)
	nod->parent = nod->right;
	Node<K, V>* aux = nod->parent->left;
	nod->parent->left = nod;

	//legatura cu fostul arbore stang al parintelui
	nod->right = aux;
	aux->parent = nod;
}

template<typename K, typename V, typename F>
void Dictionary<K, V, F>::rotate_right(Node<K, V>& nod) {
	//daca este fiu stang
	if (nod == nod->parent->left) {
		//legatura parinte cu fiu stang
		nod->parent->left = nod->left;
		nod->left->parent = nod->parent;
	}

	//daca este fiu drept
	else {
		//legatura parinte cu fiu stang
		nod->parent->right = nod->left;
		nod->left->parent = nod->parent;
	}

	//legatura nod cu noul parinte (fiul stang)
	nod->parent = nod->left;
	Node<K, V>* aux = nod->parent->right;
	nod->parent->right = nod;

	//legatura cu fostul arbore drept al parintelui
	nod->left = aux;
	aux->parent = nod;
}

//constructor fara parametrii
template <typename K, typename V, typename F>
inline Dictionary<K, V, F>::Dictionary() : root(NULL){}

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

//metoda de adaugat valori in dictionar
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::push(const K& k, const V& v) {
	int ok = 1;

	//caut si inserez perechea data in locul potrivit din arbore
	Node<K, V> p = root;
	Node<K, V> pred = root;
	while (p && ok) {
		pred = p;

		//daca cheile sunt egale
		if (!cmp(p->key, k) && !cmp(k, p->key)) {
			p->value = v;
			ok = 0;
		}

		//daca cheia data este mai mica decat cheia din nodul curent
		else if (cmp(k, p->key))
			p = p->left;

		//daca chiea data este mai mare decat cheia din nodul curent
		else
			p = p->right;
	}

	//daca cheia nu mai exista deja in arbore o adaug
	//si ma asigur sa se mentina proprietatile de red black tree
	if (ok) {
		p = new Node<K, V>(k, v);
		p->parent = pred;

		//daca arborele nu avea radacina, o creez
		//si colorez radacina cu negru
		if (pred == NULL)
			this->root = p;

		else {
			//daca e fiu stang
			if (cmp(k, pred->key))
				pred->left = p;

			//daca e fiu drept
			else
				pred->right = p;
		}


		//cata vreme culoare lui p este rosu
		while (p->color == "red") {
			//daca p este radacina, il coloram negru
			if (p == root)
				p->color = "black";

			else {
				//arborele genealogic al lui p (pun intended)
				Node<K, V>* parent = p->parent;
				Node<K, V>* grandparent = parent->parent;
				Node<K, V>* uncle;

				//daca e fiu stang
				if (parent->left == p)
					uncle = grandparent->right;

				//daca e fiu drept
				else
					uncle = grandparent->right;

				//daca exista 'bunicul' lui p
				if (grandparent) {
					//verific daca 'unchiul' nodului p este rosu
					//caz in care ii recolorez 'parintele', 'bunicul' si 'unchiul'
					if (uncle->color == "red") {
						grandparent->recolorare();
						parent->recolorare();
						uncle->recolorare();
						p = grandparent;
					}

					//daca 'unchiul' lui p este negru
					else {
						//daca p formeaza cu 'parintele' si 'bunicul' sau un triunghi la stanga
						//rotim parintele lui p la dreapta
						if (parent->left == p && grandparent->right == parent) {
							this->rotate_right(parent);
							p = parent;
						}

						//daca p formeaza cu 'parintele' si 'bunicul' sau un triunghi la dreapta
						//rotim 'parintele' lui p la stanga
						else if (parent->right == p && grandparent->left == parent) {
							this->rotate_left(parent);
							p = parent;
						}

						//daca p formeaza cu 'parintele' si 'bunicul' sau o linie,
						//iar 'bunicul' lui p se afla in stanga lui
						//rotim 'bunicul' lui p la stanga
						//si recoloroam 'bunicul' si 'patintele'
						else if (parent->right == p && grandparent->right == parent) {
							this->rotate_left(grandparent);
							grandparent->recolorare();
							parent->recolorare();
							p = parent;
						}

						//daca p formeaza cu 'parintele' si 'bunicul' sau o linie,
						//iar 'bunicul' lui p se afla in dreapta lui
						//rotim 'bunicul' lui p la dreapta
						//si recoloroam 'bunicul' si 'patintele'
						else if (parent->right == p && grandparent->right == parent) {
							this->rotate_right(grandparent);
							grandparent->recolorare();
							parent->recolorare();
							p = parent;
						}
					}
				}
			}
		}
	}
}

//metoda de cautare in arbore dupa o anumita cheie ce intoarce
//nodul ce contine cheia respectiva, sau NULL daca aceasta nu exista
template<typename K, typename V, typename F>
Node<K, V>* Dictionary<K, V, F>::search(const K& k) const {
	Node<K, V>* p = this->root;
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

//metoda de golire a dictionarului
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::clear() {
	while (this->root)
		this->pop(root->key);
}

//operator de atribuire
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::operator =(const Dictionary<K, V, F>& D) {
	//daca elementul curent este diferit de cel primit
	if (this != D) {
		//sterg elementul curent
		this->~Dictionary();

		//parcurg dictionarul primit si adaug fiecare 
		//pereche (key, value) in obiectul curent
		deque<Node<K, V>*> q;
		q.push_back(D.root);
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

//operator << (afisare)
template <typename K, typename V, typename F>
ostream& operator << (ostream& out, const Dictionary<K, V, F>& D) {
	//parcurg dictionarul primit
	deque<Node<K, V>*> q;
	q.push_back(D.root);
	while (q) {
		//daca nodul curent are fiu stang il adaug in coada
		if (q.front->left != NULL)
			q.push_back(q.front->left);

		//daca nodul curent are fiu drept il adaug in coada
		if (q.front->right != NULL)
			q.push_back(q.front->right);
	
		//afisez perechea (cheie, valoare) din nodul curent
		out << "(" << q.front->key << ", " << q.front->value << ")" << endl;

		//scot nodul din coada
		q.pop_front();
	}

	return out;
}