#ifndef __CLOTHES_H
#define __CLOTHES_H

#include "SearchTree.h"
#include "List.h" 

template <class Shop, class Model, class Pieces>
class Clothes {
private:
	class Node {
	public:
		Node() : _rg(NULL) {}
		Node(const Model &clave, const Pieces &valor)
			: _key(clave), _value(valor), _rg(NULL) {}
		Node(const Model &clave, const Pieces &valor, Node *dr)
			: _key(clave), _value(valor), _rg(dr) {}

		Model _key;
		Pieces _value;
		Node *_rg;
	};

	SearchTree<Shop, Node*> _tree;
public:

	/*
		Builder to create the clothing company without pieces of cloth.
		Instantiating a search tree.
		Complexity: constant.
	*/
	void Create() {
		_tree = SearchTree<Shop, Node*>();
	}

	/*
		It adds a shop to the search tree with a given name in the input parameter. If it already exists, it ignores the operation. 
		Complexity: constant.
	*/
	void addShop(Shop shop) {
		if (!_tree.exists(shop)) {
			_tree.insert(shop, NULL);
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

			Node* prevModels = _tree.get(shop);	
			Node* curr = prevModels;
			Node* prev = curr;

			while (curr != NULL && !found) {
				if (curr->_key == model) {
					curr->_value = curr->_value + n;
					prev->_rg = curr->_rg;
					Node* modelNode = new Node(model, curr->_value, prevModels);
					_tree.insert(shop, modelNode);
					found = true;
				}
				else {
					prev = curr;
					curr = curr->_rg;
				}
			}
			
			if (!found) {
				Node* modelNode = new Node(model, n, prevModels);
				_tree.insert(shop, modelNode);
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
		List<Model> list = List<Model>();
		if (_tree.exists(shop)) {
			Node* model = _tree.get(shop);
			for (int i = 0; i < n && model != NULL; ++i) {
				list.push_back(model->_key);
				model = model->_rg;
			}
		}

		return list;
	}

	/*
		It returns a list of the shops shorted alphabetically.  
		Complexity: linear. Iterates all the shops of the tree.
	*/
	List<Shop> shops() {
		List<Shop> list = List<Shop>();
		if (!_tree.empty()) {
			typename SearchTree<Shop, Node*>::Iterator it = _tree.begin();
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
			Node* modelNode = _tree.get(shop);

			while (modelNode != NULL && !found) {
				if (modelNode->_key == model) {
					p = modelNode->_value;
					found = true;
				}
				else
					modelNode = modelNode->_rg;
			}
		}
		return p;
	}
};

#endif