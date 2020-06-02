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

int addBT(Bintree<int> root, int depth, int counter) {
	if (root.empty())
		return 0;
	if (counter >= depth) {
		return (root.root()) + addBT(root.leftChild(), depth, counter + 1) + addBT(root.rightChild(), depth, counter + 1);
	}
	else {
		return addBT(root.leftChild(), depth, counter + 1) + addBT(root.rightChild(), depth, counter + 1);
	}
}

int main() {
	int depth_threshold, cases;
	
	cin >> cases;
	while (cases--) {
		Bintree<int> tree = readBintree();
		cin >> depth_threshold;
		cout << addBT(tree, depth_threshold, 0) << endl;
	}
	return 0;
}