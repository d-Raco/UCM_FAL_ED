#include <iostream>
#include "Bintree.h"
#include "List.h"
using namespace std;

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

//It has a linear complexity, because traverses each node once.

int special(Bintree<int> root, int &num, int prev) {
	if (root.empty()) {
		if (prev == 1)
			num++;
		return 1;
	}
	else {
		int sum = 1;
		if (!root.leftChild().empty())
			sum = special(root.leftChild(), num, prev * root.root());
		
		if (!root.rightChild().empty())
			sum *= special(root.rightChild(), num, prev * root.root());
		
		if (sum == prev)
			num++;
		return sum * root.root();
	}
}

int main() {
	int num, cases;

	cin >> cases;
	while (cases--) {
		Bintree<int> tree = readBintree();
		num = 0;
		if (tree.empty())
			cout << 0 << endl;
		else {
			special(tree, num, 1);
			cout << num << endl;
		}
	}
	return 0;
}