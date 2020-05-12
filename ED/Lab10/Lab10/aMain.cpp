#include <iostream>
#include "SearchTree.h"
#include <string>
using namespace std;

int main() {
	int cases, points, n;
	string names;
	SearchTree<string, int> searchtree = SearchTree<string, int>();

	cin >> cases;
	while (cases--) {
		cin >> n;
		if (n == 0) {
			cout << endl;
		}
		else {
			for (int i = 0; i < n; ++i) {
				cin >> names;
				cin >> points;
				if (searchtree.exists(names)) {
					searchtree.insert(names, points + searchtree.get(names));
				}
				else{
					searchtree.insert(names, points);
				}
			}
			SearchTree<string, int>::Iterator it = searchtree.begin();
			while (it != searchtree.end()) {
				cout << "(" << it.key() << ":" << it.value() << ")";
				searchtree.remove(it.key());
				it = searchtree.begin();
			}
			cout << endl;
		}
	}
	return 0;
}

