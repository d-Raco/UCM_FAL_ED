//Ramón Costales de Ledesma
// EDp7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Bintree.h"
#include "List.h"
using namespace std;
Bintree<int> readBintree();


/* It solves the case for a given input binary tree, and returns
the number.
The student should implement this function and probably
the generalization of this function. 

It has a linear complexity, because the function traverses each node only once.

*/
int solveCase(Bintree<int> t, int prevOdds, int &special) {
	if (!t.empty()) {
		int odds = prevOdds;
		if (t.root() % 2 != 0)
			++odds;
		int oddsBellow = solveCase(t.leftChild(), odds, special) + solveCase(t.rightChild(), odds, special);

		if (prevOdds > oddsBellow)
			++special;

		return t.root() % 2 + oddsBellow;
	}
	else
		return 0;
}



/* Main function*/
int main()
{
	int numCases;
	cin >> numCases;
	for (int i = 0; i < numCases; i++) {
		Bintree<int> t = readBintree();
		int special = 0;
		solveCase(t, 0, special);
		cout << special << endl;
	}
}


// It reads a binary tree of integers from the standard input
Bintree<int> readBintree() {
	char c;
	cin >> c;
	switch (c) {
	case '#': return Bintree<int>();
	case '[': {
		int raiz;
		cin >> raiz;
		cin >> c;
		return Bintree<int>(raiz);
	}
	case '(': {
		Bintree<int> left = readBintree();
		int root;
		cin >> root;
		Bintree<int> right = readBintree();
		cin >> c;
		return Bintree<int>(left, root, right);
	}
	default:
		return Bintree<int>();
	}
}
