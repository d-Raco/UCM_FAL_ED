#ifndef __CLOTHES_H
#define __CLOTHES_H

#include "SearchTree.h"
#include "List.h" 

template <class Shop, class Model, class Pieces>
class Clothes {
private:
	class Node {
	public:
		Node(const Model &clave, const Pieces &valor)
			: _key(clave), _value(valor) {}

		Model _key;
		Pieces _value;
	};

	SearchTree<Shop, List<Node>*> _tree;
public:

	/*
		Builder to create the clothing company without pieces of cloth.
		Instantiating a search tree.
		Complexity: constant.
	*/
	void Create() {
		_tree = SearchTree<Shop, List<Node>*>();
	}

	/*
		It adds a shop to the search tree with a given name in the input parameter. If it already exists, it ignores the operation. 
		Complexity: constant.
	*/
	void addShop(Shop shop) {
		if (!_tree.exists(shop)) {
			List<Node> *l = new List<Node>();
			_tree.insert(shop, l);
		}
	}

	/*
		adds n cloth pieces of a new cloth model to a shop. 
		If the shop already had this model, it increments the number of pieces. 
		If the shop does not exist, it ignores the operation. 

		_tree.get() has logarithmic complexity. It's a binary search (recursive).
		The while loop has a linear complexity. Iterates all nodes of a shop.
		Complexity: n log(n).
	*/
	void addModel(Shop shop, Model model, Pieces n) {
		if (_tree.exists(shop)) {
			bool found = false;

			List<Node> *prevModels = _tree.get(shop);	
			typename List<Node>::MutableIterator it = prevModels->begin();

			while (it != prevModels->end() && !found) {
				if (it.elem()._key == model) {
					Node newNode = Node(model, it.elem()._value + n);
					it.setElem(newNode);
					prevModels->push_front(it.elem());
					it = prevModels->remove(it);
					found = true;
				}
				else
					it.next();
			}
			
			if (!found) {
				Node newNode = Node(model, n);
				prevModels->push_front(newNode);
			}
		}
	}

	/*
		It returns a list of the “n” last models added to a given shop in inverse order. 
		First, it should be the last model added. 
		Second should be the second to the last model, and so on. 
		If there are not enough last models, it only returns the available ones in this inverse order. 
		If the shop does not exist, it returns an empty list.
		
		_tree.get() has logarithmic complexity. It's a binary search (recursive).
		The for loop has a linear complexity. Iterates all nodes of a shop.
		Complexity: n log(n).
	*/
	List<Model> lastModels(Shop shop, Pieces n) {
		List<Node> *list = new List<Node>();
		List<Model> res = List<Model>();
		if (_tree.exists(shop)) {
			list = _tree.get(shop);
			typename List<Node>::Iterator it = list->cbegin();

			int i = 0;
			while (it != list->cend() && i < n) {
				res.push_back(it.elem()._key);
				it.next();
				++i;
			}
		}

		return res;
	}

	/*
		It returns a list of the shops shorted alphabetically.  
		Complexity: linear. Iterates all the shops of the tree.
	*/
	List<Shop> shops() {
		List<Shop> list = List<Shop>();
		if (!_tree.empty()) {
			typename SearchTree<Shop, List<Node>*>::Iterator it = _tree.begin();
			while (it != _tree.end()) {
				list.push_back(it.key());
				it.next();
			}
		}

		return list;
	}

	/*
		It returns the number of pieces of cloth of a given shop and model. It returns 0 if either the model or the shop does not exist.
		
		_tree.get() has logarithmic complexity. It's a binary search (recursive).
		The while loop has a linear complexity. Iterates all nodes of a shop.
		Complexity: n log(n).
	*/
	Pieces pieces(Shop shop, Model model) {
		Pieces p = 0;
		bool found = false;
		if (_tree.exists(shop)) {
			List<Node> *list = _tree.get(shop);
			typename List<Node>::Iterator it = list->cbegin();

			while (it != list->cend() && !found) {
				if (it.elem()._key == model) {
					p = it.elem()._value;
					found = true;
				}
				else
					it.next();
			}
		}
		return p;
	}
};

#endif