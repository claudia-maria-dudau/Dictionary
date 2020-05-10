#pragma once
#include "Dictionary.h"
#include <cassert>

//clasa pentru testarea functionalitatilor dictionarului
class Test{
public:
	static void test_Dictionary();
};

void Test::test_Dictionary() {
	//constructor fara parametrii
	Dictionary<int, int> d1;
	assert(d1.root == NULL);

	//push
	d1.push(1, 2);
	d1.push(2, 3);
	d1.push(1, 6);
	d1.push(3, 9);
	d1.push(4, 3);
	d1.push(5, 5);
	d1.push(7, 2);
	d1.push(6, 4);
	d1.push(8, 1);

	Node<int, int>* r1Left = d1.root->getLeft();
	Node<int, int>* r1Right = d1.root->getRight();

	assert(d1.root->getKey() == 4);
	assert(d1.root->getColor() == "black");
	assert(r1Left->getKey() == 2);
	assert(r1Left->getColor() == "red");
	assert(r1Right->getKey() == 6);
	assert(r1Right->getColor() == "red");
	assert(r1Left->getLeft()->getKey() == 1);
	assert(r1Left->getLeft()->getColor() == "black");
	assert(r1Left->getRight()->getKey() == 3);
	assert(r1Left->getRight()->getColor() == "black");
	assert(r1Right->getLeft()->getKey() == 5);
	assert(r1Right->getLeft()->getColor() == "black");
	assert(r1Right->getRight()->getKey() == 7);
	assert(r1Right->getRight()->getColor() == "black");
	assert(r1Right->getRight()->getRight()->getKey() == 8);
	assert(r1Right->getRight()->getRight()->getColor() == "red");

	//constructor de copiere / operator =
	Dictionary<int, int> d2(d1);
	Dictionary<int, int> d3 = d1;

	Node<int, int>* r2Left = d2.root->getLeft();
	Node<int, int>* r2Right = d2.root->getRight();

	assert(d2.root->getKey() == d1.root->getKey());
	assert(r2Left->getKey() == r1Left->getKey());
	assert(r2Right->getKey() == r1Right->getKey());
	assert(r2Left->getLeft()->getKey() == r1Left->getLeft()->getKey());
	assert(r2Left->getRight()->getKey() == r1Left->getRight()->getKey());
	assert(r2Right->getLeft()->getKey() == r1Right->getLeft()->getKey());
	assert(r2Right->getRight()->getKey() == r1Right->getRight()->getKey());
	assert(r2Right->getRight()->getRight()->getKey() == r1Right->getRight()->getRight()->getKey());

	//pop
	Node<int, int>* r3Left; 
	Node<int, int>* r3Right;

	d3.pop(4);
	r3Left = d3.root->getLeft();
	r3Right = d3.root->getRight();

	assert(d3.root->getKey() == 3);
	assert(d3.root->getColor() == "black");
	assert(r3Left->getColor() == "black");
	assert(r3Left->getLeft()->getColor() == "red");

	d3.pop(5);
	r3Left = d3.root->getLeft();
	r3Right = d3.root->getRight();

	assert(r3Right->getKey() == 7);
	assert(r3Right->getColor() == "red");
	assert(r3Right->getLeft()->getKey() == 6);
	assert(r3Right->getLeft()->getColor() == "black");
	assert(r3Right->getRight()->getKey() == 8);
	assert(r3Right->getRight()->getColor() == "black");
	
	d3.pop(2);
	r3Left = d3.root->getLeft();
	r3Right = d3.root->getRight();

	assert(r3Left->getKey() == 1);
	assert(r3Left->getColor() == "black");

	d3.pop(1);
	r3Left = d3.root->getLeft();
	r3Right = d3.root->getRight();

	assert(d3.root->getKey() == 7);
	assert(d3.root->getColor() == "black");
	assert(r3Left->getKey() == 3);
	assert(r3Left->getColor() == "black");
	assert(r3Left->getRight()->getKey() == 6);
	assert(r3Left->getRight()->getColor() == "red");

	d3.pop(8);
	r3Left = d3.root->getLeft();
	r3Right = d3.root->getRight();

	assert(d3.root->getKey() == 6);
	assert(d3.root->getColor() == "black");
	assert(r3Left->getKey() == 3);
	assert(r3Left->getColor() == "black");
	assert(r3Right->getKey() == 7);
	assert(r3Right->getColor() == "black");
	
	d3.pop(7);
	r3Left = d3.root->getLeft();
	r3Right = d3.root->getRight();

	assert(r3Left->getColor() == "red");
	assert(r3Right == NULL);

	//search
	assert(d1.search(1));
	assert(d1.search(2));
	assert(!d1.search(10));

	//destructor / clear
	d2.clear();
	assert(d2.root == NULL);

	//operator[]
	assert(d1[1] == 6);
	assert(d1[2] == 3);
	assert(d1[3] == 9);
	assert(d1[4] == 3);
	assert(d1[5] == 5);
	assert(d1[6] == 4);
	assert(d1[7] == 2);
	assert(d1[8] == 1);

	try {
		cout << d1[10];
		assert(false);
	}
	catch (invalid_argument e) {
		assert(true);
	}

	//specializare KeyComp pt stringuri
	Dictionary<string, int> d4;
	d4.push("unu", 1);
	d4.push("doi", 2);
	d4.push("trei", 3);
	d4.push("patru", 4);
	d4.push("cinci", 5);

	Node<string, int> * r4Left = d4.root->getLeft();
	Node<string, int>* r4Right = d4.root->getRight();

	assert(d4.root->getKey() == "trei");
	assert(r4Left->getKey() == "unu");
	assert(r4Right->getKey() == "doi");
	assert(r4Right->getLeft()->getKey() == "patru");
	assert(r4Right->getRight()->getKey() == "cinci");

	d4.push("un", 10);
	d4.push("trap", 11);
	d4.push("d", 21);
	d4.push("paine", 9);

	r4Left = d4.root->getLeft();
	r4Right = d4.root->getRight();
	
	assert(d4.root->getValue() == 11);
	assert(r4Left->getValue() == 10);
	assert(r4Right->getValue() == 21);
	assert(r4Right->getLeft()->getValue() == 4);
	assert(r4Right->getLeft()->getRight()->getKey() == "paine");

}