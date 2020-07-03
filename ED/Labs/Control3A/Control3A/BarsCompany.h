#pragma once
#include <string>
#include "List.h"
#include "SearchTree.h"
#include "Table.h"
using namespace std;

//Ramón Costales de Ledesma

// Definition of Bar and Drink types as strings
typedef string Bar;
typedef string Drink;

/* Template for the Exam about Bars, for both exam models A and B.
Implment only the methods that your exam models requires and the
attributes that you need for this purpose. 
Read the instructions carefully to know the behaviour that you 
have to implement in each funcion*/
class BarsCompany {
public:
	// Builder 
	// Complexity: constant
	BarsCompany() {
		_bar = SearchTree<Bar, Table<Drink, int>>();
		_order = Table<Bar, List<Drink>>();
	}

	// Complexity: logarithmic, because inserting in a SearchTree is logarithmic and inserting in a hash table is constant
	void addBar(Bar b) {
		if (!_bar.exists(b)) {
			Table<Drink, int> t = Table<Drink, int>();
			_bar.insert(b, t);
			List<Drink> l = List<Drink>();
			_order.insert(b, l);
		}
	}

	// Complexity: logarithmic, because geting an element in a SearchTree is logarithmic
	void addDrink(Bar b, Drink d, int n) {
		if (_bar.exists(b)) {
			if (_bar.get(b).exists(d)) {
				int value = _bar.get(b).get(d);
				_bar.get(b).insert(d, value + n);
			}
			else {
				_bar.get(b).insert(d, n);
				_order.get(b).push_back(d);
			}
		}
	}

	// Implement this only if your Exam Model is B
	void consumeDrink(Bar b, Drink d, int n) {
		// To be implemented here.
	}

	// Complexity: linear because it traverses n elements of a list
	List<Drink> firstDrinks(Bar b, int n) {
		List<Drink> ret = List<Drink>();
		if (_order.exists(b)) {
			int i = 0;
			typename List<Drink>::Iterator it = _order.get(b).cbegin();
			while (it != _order.get(b).cend() && i < n) {
				ret.push_back(it.elem());
				it.next();
			}
		}
		return ret;
	}

	// Complexity: logarithmic, because geting an element in a SearchTree is logarithmic
	int bottles(Bar b, Drink d) {
		int res = 0;
		if (_bar.exists(b)) {
			if (_bar.get(b).exists(d)) {
				res = _bar.get(b).get(d);
			}
		}
		return res;
	}
	
	// Complexity: logarithmic, because traversing elements in a SearchTree is logarithmic
	List<Bar> bars() {
		List<Bar> res = List<Bar>();
		if (!_bar.empty()) {
			typename SearchTree<Bar, Table<Drink, int>>::Iterator it = _bar.begin();
			while (it != _bar.end()) {
				res.push_back(it.key());
				it.next();
			}
		}

		return res;
	}
private:
	SearchTree<Bar, Table<Drink, int>> _bar;
	Table<Bar, List<Drink>> _order;
};
