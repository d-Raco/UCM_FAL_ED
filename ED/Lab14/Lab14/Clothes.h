#ifndef __CLOTHES_H
#define __CLOTHES_H

#include "SearchTree.h"
#include "Table.h" 

template <class Shop, class Model, class Pieces>
class Clothes {
private:
	class Node {
	public:
		Node(const Shop &clave, const Model &valor)
			: _key(clave), _value(valor) {}

		Shop _key;
		Model _value;
	};
	SearchTree<Shop, Table<Model, Pieces>*> _tree;
	List<Node> _modelOrder;
public:

	/*
		Builder to create the clothing company without pieces of cloth.
		Instantiating a search tree and a list to store the order of the models.
		Complexity: constant.
	*/
	void Create() {
		_tree = SearchTree<Shop, Table<Model, Pieces>*>();
		_modelOrder = List<Node>();
	}

	/*
		It adds a shop to the search tree with a given name in the input parameter. If it already exists, it ignores the operation. 
		Complexity: constant.
	*/
	void addShop(Shop shop) {
		if (!_tree.exists(shop)) {
			Table<Model, Pieces> *t = new Table<Model, Pieces>();
			_tree.insert(shop, t);
		}
	}

	/*
		adds n cloth pieces of a new cloth model to a shop. 
		If the shop already had this model, it increments the number of pieces. 
		If the shop does not exist, it ignores the operation. 

		_tree.get() has logarithmic complexity. It's a binary search (recursive).
		prevModels->get() has a constant complexity.
		The while loop has a linear complexity. Iterates all nodes of a shop.
		Complexity: n log(n).
	*/
	void addModel(Shop shop, Model model, Pieces n) {
		if (_tree.exists(shop)) {

			Table<Model, Pieces> *prevModels = _tree.get(shop);
			try {
				Pieces value = prevModels->get(model) + n;
				prevModels->insert(model, value);

				bool found = false;
				typename List<Node>::MutableIterator it = _modelOrder.begin();
				while (it != _modelOrder.end() && !found) {
					if (it.elem()._key == shop && it.elem()._value == model) {
						it = _modelOrder.remove(it);
						found = true;
					}
					else
						it.next();
				}
				Node n = Node(shop, model);
				_modelOrder.push_front(n);
			}
			catch (EWrongKey & e) {
				prevModels->insert(model, n);
				Node n = Node(shop, model);
				_modelOrder.push_front(n);
			}
		}
	}

	/*
		It returns a list of the “n” last models added to a given shop in inverse order. 
		First, it should be the last model added. 
		Second should be the second to the last model, and so on. 
		If there are not enough last models, it only returns the available ones in this inverse order. 
		If the shop does not exist, it returns an empty list.
		
		The while loop has a linear complexity. Iterates the elements of a list.
		Complexity: linear.
	*/
	List<Model> lastModels(Shop shop, int n) {
		List<Model> res = List<Model>();
		if (_tree.exists(shop)) {
			typename List<Node>::Iterator it = _modelOrder.cbegin();

			int i = 0;
			while (it != _modelOrder.cend() && i < n) {
				if(it.elem()._key == shop)
					res.push_back(it.elem()._value);
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
			typename SearchTree<Shop, Table<Model, Pieces>*>::Iterator it = _tree.begin();
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
		table->get() has a constant complexity.
		Complexity: log(n).
	*/
	Pieces pieces(Shop shop, Model model) {
		Pieces p = 0;
		bool found = false;
		if (_tree.exists(shop)) {
			Table<Model, Pieces> *table = _tree.get(shop);

			try {
				p = table->get(model);
			}
			catch (EWrongKey & e) {}
		}
		return p;
	}
};

#endif