#pragma once
#include "Node.h"
#include "KeyComp.h"
#include <deque>
#include <exception>

//clasa dictionar
template <typename K, typename V, typename F = KeyComp<K>>
class Dictionary {
	Node<K, V>* root;
	KeyComp<K> cmp;

protected:
	void rotate_left(Node<K, V>*);
	void rotate_right(Node<K, V>*);

public:
	Dictionary();
	Dictionary(const Dictionary<K, V, F>&);
	~Dictionary();
	void push(const K&, const V&);
	void pop(const K&);
	Node<K, V>* search(const K&) const;
	void clear();

	V operator [] (const K&) const;
	Dictionary<K, V, F>& operator =(const Dictionary<K, V, F>&);

	template <typename K, typename V, typename F>
	friend ostream& operator << (ostream&, const Dictionary<K, V, F>&);

	friend class Test;
};

//rotire nod la stanga in arbore
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::rotate_left(Node<K, V>* nod) {
	//daca nodul este radacina
	if (nod == root) {
		//mut radacina
		root = nod->right;
		root->parent = NULL;
	}

	else {
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
	}

	//legatura nod cu noul parinte (fiul drept)
	nod->parent = nod->right;
	Node<K, V>* aux = nod->parent->left;
	nod->parent->left = nod;

	//legatura cu fostul arbore stang al parintelui
	nod->right = aux;

	//daca exista subarbore stang il leg de nod
	if (aux)
		aux->parent = nod;
}

//rotire nod la dreapta in arbore
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::rotate_right(Node<K, V>* nod) {
	//daca nodul este radacina
	if (nod == root) {
		//mut radacina
		root = nod->left;
		root->parent = NULL;
	}

	else {
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
	}

	//legatura nod cu noul parinte (fiul stang)
	nod->parent = nod->left;
	Node<K, V>* aux = nod->parent->right;
	nod->parent->right = nod;

	//legatura cu fostul arbore drept al parintelui
	nod->left = aux;

	//daca exista subarbore drept
	//il leg de nod
	if (aux)
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
	Node<K, V>* p = root;
	Node<K, V>* pred = root;
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
		while (p->parent && p->parent->color == "red") {
			//arborele genealogic al lui p (pun intended)
			Node<K, V>* parent = p->parent;
			Node<K, V>* grandparent = parent->parent;
			Node<K, V>* uncle;

			//daca exista 'bunicul' lui p
			if (grandparent) {
				//daca 'parintele' e fiu stang
				if (grandparent->left == parent)
					uncle = grandparent->right;

				//daca e fiu drept
				else
					uncle = grandparent->left;

				//verific daca 'unchiul' nodului p este rosu
				//caz in care ii recolorez 'parintele', 'bunicul' si 'unchiul'
				if (uncle && uncle->color == "red") {
					grandparent->color = "red";
					parent->color = uncle->color = "black";
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
						parent->swapColor(grandparent);
					}

					//daca p formeaza cu 'parintele' si 'bunicul' sau o linie,
					//iar 'bunicul' lui p se afla in dreapta lui
					//rotim 'bunicul' lui p la dreapta
					//si recoloroam 'bunicul' si 'patintele'
					else if (parent->right == p && grandparent->right == parent) {
						this->rotate_right(grandparent);
						parent->swapColor(grandparent);
					}
				}
			}
		}

		//daca p este radacina, il coloram negru
		if (p == root)
			p->color = "black";
	}
}

//metoda de eliminare valori din dictionar dupa cheie
template<typename K, typename V, typename F>
void Dictionary<K, V, F>::pop(const K& k) {
	//daca dictionarul este gol
	if (root == NULL)
		throw underflow_error("Dictionarul este vid");

	Node<K, V>* p = this->search(k);
	Node<K, V>* parent;
	Node<K, V>* u;

	//verific daca exista valoare cautata in arbore
	if (p) {
		//daca p are ambii fii
		if(p->right && p->left) {
			//cautam cel mai din dreapta fiu al fiului stang a lui p
			Node<K, V>* aux = p->left;
			while (aux->right)
				aux = aux->right;

			//schimb val lui p cu cele ale lui aux
			p->key = aux->key;
			p->value = aux->value;
			p = aux;
		}
		
		parent = p->parent;
		
		//daca nodul este radacina
		if (p == root) {
			//daca p are fiu stang, fac legatura intre acesta si radacina
			if (p->left) {
				root = p->left;
				p->left->parent = NULL;
				u = p->left;
			}

			//daca are fiu drept
			else if (p->right){
				root = p->right;
				p->right->parent = NULL;
				u = p->right;
			}

			//daca nu are nici un fiu inseamna ca
			//arborele contine doar radacina
			//prin urmare sterg radacina si ies
			//intrucat nu are sens sa verific
			//daca se pastreaza proprietatile de rbt
			else {
				delete p;
				root = NULL;
				return;
			}
		}
		
		else {
			//daca p este fiu stang
			if (parent->left == p) {
				//daca p are fiu stang, fac legatura intre acesta si radacina
				if (p->left) {
					parent->left = p->left;
					p->left->parent = parent;
					u = p->left;
				}

				//daca are fiu drept, sau nici un fiu
				else {
					parent->left = p->right;
					u = p->right;

					//daca exista fiul drept il leg de parinte
					if (p->right)
						p->right->parent = parent;
				}
			}

			//daca p este fiu drept
			else {
				//daca p are fiu stang, fac legatura intre acesta si radacina
				if (p->left) {
					parent->right = p->left;
					p->left->parent = parent;
					u = p->left;
				}

				//daca are iu drept, sau nici un fiu
				else {
					parent->right = p->right;
					u = p->right;

					//daca exista fiul drept il leg de parinte
					if (p->right)
						p->right->parent = parent;
				}
			}
		}

		string colorP = p->color;

		//sterg nodul p
		delete p;

		//ma asigur ca se respecta proprietatile de rbt,
		//fixand eventualele probleme care pot aparea

		string colorU = !u ? "black" : u->color;

		//daca culoarea lui p era rosu
		//coloram nodul u negru, daca acesta exista
		if (colorP == "red") {
			if (u)
				u->color = "black";
		}

		//daca p era nod negru
		else {
			//daca nodul u este rosu, il colorez negru
			//(nu este nevoie sa i se verifice exsitenta,
			//deoarece nodurile NULL sunt negre)
			if (colorU == "red")
				u->color = "black";
			
			//daca nodul u este si el negru
			else {
				//nodul u devine un nod negru dublu
				colorU = "black_black";

				//cata vreme culoare nodului u este negru_negru,
				//iar u nu este radacina
				while (colorU == "black_black" && u != root) {
					Node<K, V>* sibling = parent->right == u ? parent->left : parent->right;

					//daca culoarea 'fratelui' este rosu
					if (sibling->color == "red") {
						//coloram 'fratele' negru, iar 'parintele' rosu
						sibling->color = "black";
						parent->color = "red";

						//daca 'fratele' este fiu stang
						//rotim 'parintele' in dreapta
						if (parent->left == sibling)
							this->rotate_right(parent);

						//daca 'fratele' este fiu drept
						//rotim 'parintele in stanga
						else
							this->rotate_left(parent);
					}

					//daca 'fratele' este negru
					else {
						//determin culorile copiilor 'fratelui'
						string colorNephewLeft = !sibling->left ? "black" : sibling->left->color;
						string colorNephewRight = !sibling->right ? "black" : sibling->right->color;

						//daca 'fratele' are amandoi copii negri
						if(colorNephewLeft == "black" && colorNephewRight == "black"){
							sibling->color = "red";

							//nodul parinte va deveni noul nod dublu negru
							u = parent;
							parent = parent->parent;

							//daca 'parintele' era rosu, atunci il facem negru
							//rosu + dublu negru => negru
							if (u->color == "red")
								u->color = colorU = "black";
						}

						//daca 'fratele' are cel putin un fiu rosu
						else {
							Node<K, V>* redNephew;

							//daca 'nepotul' stang este rosu
							if (colorNephewLeft == "red") {
								redNephew = sibling->left;

								//daca 'fratele' este fiu stang
								//rotesc 'parintele' la stanga
								//si colorez nepotul in negru, 
								//restabilind astfel proprietatile de rbt
								//(acelasi numar de noduri negre in fiecare subarbore)
								if (parent->left == sibling) {
									redNephew->color = "black";
									this->rotate_right(parent);
									colorU = "black";

									if(colorNephewRight != "red")
										parent->swapColor(sibling);
								}

								//daca 'fratele' este fiu drept
								//rotesc 'fratele' la dreapta si
								//recolorez 'fratele' in rosu si 'nepotul' in negru
								else {
									sibling->swapColor(redNephew);
									this->rotate_right(sibling);
								}
							}

							//daca 'nepotul' drept este rosu
							else {
								redNephew = sibling->right;

								//daca 'fratele' este fiu stang
								//rotesc 'fratele' la stanga si
								//recolorez 'fratele' in rosu, iar 'nepotul' in negru
								if (parent->left == sibling) {
									sibling->swapColor(redNephew);
									this->rotate_left(sibling);
								}

								//daca 'fratele' este fiu drept
								//rotesc parintele la stanga
								//si colorez nepotul in negru, 
								//restabilind astfel proprietatile de rbt
								//(acelasi numar de noduri negre in fiecare subarbore)
								else {
									redNephew->color = "black";
									this->rotate_left(parent);
									parent->swapColor(sibling);
									colorU = "black";
								}
							}
						}
					}
				}
			}
		}
	}

	//daca cheia transmisa nu exista in dictionar
	else 
		throw invalid_argument("Cheia nu exista in dictionar");
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
	while (this->root != NULL)
		this->pop(root->key);
}

//operator de atribuire
template<typename K, typename V, typename F>
Dictionary<K, V, F>& Dictionary<K, V, F>::operator =(const Dictionary<K, V, F>& D) {
	//daca elementul curent este diferit de cel primit
	if (this != &D) {
		//sterg elementul curent
		this->~Dictionary();

		//parcurg dictionarul primit si adaug fiecare 
		//pereche (key, value) in obiectul curent
		deque<Node<K, V>*> q;
		q.push_back(D.root);
		while (q.size()) {
			Node<K, V>* front = q.front();

			//daca nodul curent are fiu stang il adaug in coada
			if (front->left != NULL)
				q.push_back(front->left);

			//daca nodul curent are fiu drept il adaug in coada
			if (front->right != NULL)
				q.push_back(front->right);

			//adaug nodul curent in dictionar
			this->push(front->key, front->value);
			q.pop_front();
		}

		return *this;
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
	while (q.size()) {
		Node<K, V>* front = q.front();

		//daca nodul curent are fiu stang il adaug in coada
		if (front->getLeft() != NULL)
			q.push_back(front->getLeft());

		//daca nodul curent are fiu drept il adaug in coada
		if (front->getRight() != NULL)
			q.push_back(front->getRight());
	
		//afisez perechea (cheie, valoare) din nodul curent
		out << "(" << front->getKey() << ", " << front->getValue() << ")" << " ";

		//scot nodul din coada
		q.pop_front();
	}

	return out;
}