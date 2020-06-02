
#ifndef DECK_H
#define DECK_H
#include <algorithm>
#include "SearchTree.h"
class Deck {
public:
	Deck() {
		_searchTree = SearchTree<int, int>();
	};

	void addStickers(int stickerModel, int numStickers) {
		_searchTree.insert(stickerModel, numStickers);
	};

	int getNumStickers(int stickerModel) {
		return _searchTree.get(stickerModel);
	};

	int numCommonStickers(Deck *deck) {
		SearchTree<int, int>::Iterator it = _searchTree.begin();
		int sum = 0;
		while (it != _searchTree.end()) {
			try {
				sum += std::min(it.value(), deck->getNumStickers(it.key()));
			}
			catch (const EWrongKey&) {}
			it.next();
		}
		return sum;
	};

private:
	SearchTree<int,int> _searchTree;
};






#endif