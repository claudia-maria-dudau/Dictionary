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
	assert(r1Left->getKey() == 2);
	assert(r1Right->getKey() == 6);
	assert(r1Left->getLeft()->getKey() == 1);
	assert(r1Left->getRight()->getKey() == 3);
	assert(r1Right->getLeft()->getKey() == 5);
	assert(r1Right->getRight()->getKey() == 7);
	assert(r1Right->getRight()->getRight()->getKey() == 8);

	//constructor de copiere / operator =
	Dictionary<int, int> d2(d1);

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

	//search
	assert(d1.search(1));
	assert(d1.search(2));
	assert(!d1.search(10));

	//destructor / clear

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
}