#include <iostream>
#include <string>
#include "Table.h"
using namespace std;

int main() {
	Table<string, Table<string, Table<string, int>>> table = Table<string, Table<string, Table<string, int>>>();
	int cases, num_operations, priority;
	string op, ID, name, type;
	cin >> cases;
	while (cases--) {
		cin >> num_operations;
		for (int i = 0; i < num_operations; ++i) {
			cin >> op;
			if (op == "add") {
				cin >> ID;
				cin >> name;
				cin >> type;
				cin >> priority;
			}
			else if (op == "get") {
				cin >> ID;
			}
			else if (op == "next") {

			}
			else if (op == "remove") {

			}
			else if (op == "empty") {

			}
			else {
				cout << "Error command" << endl; //exception
			}
		}

		Table<string, Table<string, Table<string, int>>>::Iterator it = table.begin();
		while (it != table.end()) {
			table.remove(it.key());
			it = table.begin();
		}
	}

	return 0;
}
