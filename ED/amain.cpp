#include <string>
#include <iostream>
#include "List.h"
#include "Clothes.h"
using namespace std;

int main() {
	Clothes<string, string, int> clothes = Clothes<string, string, int>();
	clothes.Create();

	string input, shop, model;
	int pieces;
	cin >> input;
	while (input != "end") {
		while (input != "end") {
			if (input == "addShop") {
				cin >> shop;
				clothes.addShop(shop);
			}

			else if (input == "addModel") {
				cin >> shop;
				cin >> model;
				cin >> pieces;
				clothes.addModel(shop, model, pieces);
			}

			else if (input == "lastModels") {
				cin >> shop;
				cin >> pieces;
				List<string> l = clothes.lastModels(shop, pieces);

				if (!l.empty()) {
					cout << l.front();
					l.pop_front();
					while (!l.empty()) {
						cout << "," << l.front();
						l.pop_front();
					}
				}
				cout << endl;
			}

			else if (input == "shops") {
				List<string> l = clothes.shops();

				if (!l.empty()) {
					cout << l.front();
					l.pop_front();
					while (!l.empty()) {
						cout << "," << l.front();
						l.pop_front();
					}
				}
				cout << endl;
			}

			else if (input == "pieces") {
				cin >> shop;
				cin >> model;
				cout << clothes.pieces(shop, model) << endl;
			}

			cin >> input;
		}
		clothes.Create();
		cin >> input;
	}

	return 0;
}
