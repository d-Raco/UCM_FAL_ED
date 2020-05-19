#include <iostream>
#include <string>
#include "LawTable.h"
using namespace std;

/*
CREATE Y COMPLEJIDAD
*/


int main() {
	LawTable<string, string, string, int> table = LawTable<string, string, string, int>();
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
				table.addCase(ID, name, type, priority);
			}
			else if (op == "get") {
				cin >> ID;
				try {
					table.getCase(ID, name, type);
					cout << name << " " << type << endl;
				}
				catch (EWrongKey & e) {
					cout << e.msg() << endl;
				}
			}
			else if (op == "next") {
				try {
					table.nextCase(ID, priority);
					cout << ID << " " << priority << endl;
				}
				catch (EEmpty & e) {
					cout << e.msg() << endl;
				}
			}
			else if (op == "remove") {
				table.removeNextCase();
			}
			else if (op == "empty") {
				if (table.empty())
					cout << "yes" << endl;
				else
					cout << "no" << endl;
			}
		}
		
		while (!table.empty()) {
			table.removeNextCase();
		}
	}

	return 0;
}
