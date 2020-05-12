#include <iostream>
#include "Bintree.h"
#include "List.h"
using namespace std;

Bintree<char> readBintree() {
	char c;
	cin >> c;
	switch (c) {
	case '#': return Bintree<char>();
	case '[': {
		char raiz;
		cin >> raiz;
		cin >> c;
		return Bintree<char>(raiz);
	}
	case '(': {
		Bintree<char> left = readBintree();
		char root;
		cin >> root;
		Bintree<char> right = readBintree();
		cin >> c;
		return Bintree<char>(left, root, right);
	}
	default:
		return Bintree<char>();
	}
}

//It has a linear complexity, because traverses each node once.

bool covid19(Bintree<char> root, int& num) {
	bool checky1, checky2;
	if (root.empty()) {
		return false;
	}
	else {
		checky1 = covid19(root.leftChild(), num);
		checky2 = covid19(root.rightChild(), num);
		checky1 |= checky2;
		if (root.root() == 'P' && !checky1) {
			num++;
		}
		if (root.root() == 'S') {
			checky1 = true;
		}
		return checky1;
	}
}

int main() {
	int num, cases;

	cin >> cases;
	while (cases--) {
		Bintree<char> tree = readBintree();
		num = 0;
		covid19(tree, num);
		cout << num << endl;
	}
	return 0;
}