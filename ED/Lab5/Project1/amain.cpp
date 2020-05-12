#include <iostream>
#include "List.h"
using namespace std;

int main() {
	List<int> list;
	int numMembers, fingers, counter = 1;

	while (cin >> numMembers && numMembers >= 1) {
		for (int i = 1; i <= numMembers; i++) {
			list.push_back(i);
		}
		List<int> ::MutableIterator iter = list.begin();
		cin >> fingers;
		while (list.numElems() > 1) {
			if (counter == fingers) {
				iter = list.remove(iter);
				if (iter == list.end()) {
					iter = list.begin();
				}
				counter = 1;
			}
			else {
				if (iter.elem() == list.back())
					iter = list.begin();
				else
					iter.next();
				counter++;
			}
		}
		cout << list.elem(0) << endl;
		list.remove(iter);
	}
	return 0;
}