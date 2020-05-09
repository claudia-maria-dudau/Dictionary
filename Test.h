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
	cout << d1;

	//constructor de copiere

	//pop

	//search

	//clear

	//operator[]

	//operator =
}