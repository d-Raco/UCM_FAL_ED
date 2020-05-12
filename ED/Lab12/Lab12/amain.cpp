#include <iostream>
#include <string>
#include "Table.h"
using namespace std;

int main()
{
	Table<string, Table<string, int>> table = Table<string, Table<string, int>>();
	int cases, operations, m;
	string p1, a1, p2, a2;
	char c;
	cin >> cases;
	while (cases--) {
		cin >> operations;
		for (int i = 0; i < operations; ++i) {
			cin >> c;
			switch (c) {
			case 'd':
				cin >> p1;
				cin >> a1;
				cin >> m;
				table.deposit(p1, a1, m);
				break;
			case 't':
				cin >> p1;
				cin >> a1;
				cin >> p2;
				cin >> a2;
				cin >> m;
				table.transfer(p1, a1, p2, a2, m);
				break;
			case 'm':
				cin >> p1;
				cout << table.money(p1) << endl;
				break;
			}
		}
		Table<string, Table<string, int>>::Iterator it = table.begin();
		while (it != table.end()) {
			table.remove(it.key());
			it = table.begin();
		}
	}
		
	return 0;
}
