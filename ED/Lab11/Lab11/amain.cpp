#include <iostream>
#include "Deck.h"
#include "SearchTree.h"
#include <string>
using namespace std;

void readDeck(Deck *d) {
	char c;
	string line;
	int value, key;
	cin >> c;
	cin >> line;
	if (line.at(0) != ']') {
		key = stoi(line);
		cin >> c;
		cin >> value;
		cin >> c;
		d->addStickers(key, value);
		while (c != ']') {
			cin >> key;
			cin >> c;
			cin >> value;
			cin >> c;
			d->addStickers(key, value);
		}
	}
	
}

int main() {
	int cases;
	cin >> cases;
	while (cases--) {
		Deck *d1 = new Deck(); 
		Deck *d2 = new Deck();
		readDeck(d1);
		readDeck(d2);
		cout << d1->numCommonStickers(d2) << endl;
	}
	return 0;
}