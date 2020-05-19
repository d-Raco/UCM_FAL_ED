#ifndef __LAWTABLE_H
#define __LAWTABLE_H

#include "Exceptions.h"

#include <cassert>

template <class C, class N, class T, class V>
class LawTable {
private:

	/**
	 * The table contains an array of pointers to nodes indexed by the priority. Each node contains a
	 * key, a name, a type and a pointer to the next node.
	 */
	class Node {
	public:
		/* Builders. */
		Node(const C &key, const N &name, const T &type) :
			_key(key), _name(name), _type(type), _next(NULL) {};

		Node(const C &key, const N &name, const T &type, Node *next) :
			_key(key), _name(name), _type(type), _next(next) {};

		/* Atributos públicos. */
		C _key;
		N _name;
		T _type;
		Node *_next;  // Puntero al siguiente Node.
	};

public:

	/**
	 * Initial table size.
	 */
	static const int INITIAL_SIZE = 3;

	/**
	 * This is the Create function.
	 * Creates a table with INITIAL_SIZE
	 * positions.
	 * Complexity: constant. We only do the iteration of the for loop 3 times.
	 */
	LawTable() : _v(new Node*[INITIAL_SIZE]), _size(INITIAL_SIZE), _numElems(0) {
		for (unsigned int i = 0; i < _size; ++i) {
			_v[i] = NULL;
		}
	}

	/**
	 * Destructor.
	 */
	~LawTable() {
		free();
	}

	/**
	 * insert a new Node (key, name, type, next Node) in the table indexed by the value (priority). 
	 *
	 * @param key key of the new element.
	 * @param name name of the new element.
	 * @param type type of the new element.
	 * @param value priority of the new element.
	 * Complexity: constant. It only consists of an if/else. There are no loops.
	 */
	void addCase(const C &key, const N &name, const T &type, const V &value) {

		if(_v[value] == NULL)
			_v[value] = new Node(key, name, type, _v[value]);
		else
			_v[value]->_next = new Node(key, name, type, _v[value]->_next);
		
		_numElems++;
	}

	/*
	 * It stores the id of the next case and its priority to be handled, in the two output parameters. 
	 * Complexity: constant. The for loop is going to iterate the array at most 3 times.
	 */
	void nextCase(C &id, V &priority) {
		bool found = false;
		for (int prior = 0; !found && prior < 3; ++prior) {
			if (_v[prior] != NULL) {
				id = _v[prior]->_key;
				priority = prior;
				found = true;
			}
		}
		
		if (!found) {
			throw EEmpty("There are no cases");
		}
	}


	/**
	 * Remove the element from the table with highest priority and firstly added. If there was no
	 * element with this key, the table is not modified.
	 * Complexity: constant. It calls the function nextCase which is constant and we don't do anything to add to that complexity.
	 */
	void removeNextCase() {
		C key;
		V priority;
		try {
			nextCase(key, priority);

			Node *curr = _v[priority];
			_v[priority] = curr->_next;

			delete curr;
			_numElems--;
		}
		catch (EEmpty & e) {
		}
	}

	/*
	 * In “name” and “type” output parameters, it stores the information of the case with the given “id”. 
	 * If there is not such case, it should raise an error “This case does not exist” 
	 * Complexity: linear. Iterates every Node only one time. 
	*/
	void getCase(const C &key, N &name, T &type) {
		bool found = false;
		Node *node = NULL;

		// We're looking for a node that contains that key.
		for (int i = 0; !found && i < 3; ++i) {
			node = searchNodeCall(key, _v[i]);
			if (node != NULL)
				found = true;
		}
		if (node == NULL)
			throw EWrongKey("This case does not exist");

		name = node->_name;
		type = node->_type;
	}

	/**
	 * Indicates if the table is empty, that is, if it does not contain any
	 * item.
	 *
	 * @return if the table is empty.
     * Complexity: constant. Only a comparison.
	 */
	bool empty() const {
		return _numElems == 0;
	}

	
private:

	/**
	 * free all the dynamic memory reserved for the table.
	 */
	void free() {

		// free the lists of nodes
		for (unsigned int i = 0; i < _size; i++) {
			freeNodes(_v[i]);
		}

		// We release the array of pointers to Nodes.
		if (_v != NULL) {
			delete[] _v;
			_v = NULL;
		}
	}

	/**
	 * free one node and all the following.
	 *
	 * @param first node of the list to free
	 */
	static void freeNodes(Node *first) {

		while (first != NULL) {
			Node *aux = first;
			first = first->_next;
			delete aux;
		}
	}


	/**
	 * Search for a Node from the Node "curr" that contains the given key. If you
	 * find, "curr" will be pointed to that Node.
	 * If it does not find it, "curr" will be pointed to NULL.
	 *
	 * @param key key to the Node you're looking for.
	 * @param curr [in/out] initially indicates the first Node of the search and
	 * at the end indicates the Node found or NULL.
	 */
	static void searchNode(const C &key, Node* &curr) {
		bool found = false;
		while ((curr != NULL) && !found) {

			// Check if the current Node contains the searched key
			if (curr->_key == key) {
				found = true;
			}
			else {
				curr = curr->_next;
			}
		}
	}

	/**
	 * Search for a Node from "first" that contains the given key.
	  * Unlike the other "searchNode" method, it does not return a pointer to the
	 * previous node.
	 *
	 * @param key key to the Node you're looking for.
	 * @param first Node from which to perform the search.
	 * @return Node found o NULL.
	 */
	static Node* searchNodeCall(const C &key, Node *first) {
		Node *curr = first;
		searchNode(key, curr);
		return curr;
	}

	Node **_v;               ///< Array de punteros a Node.
	unsigned int _size;       ///< Tama�o del array _v.
	unsigned int _numElems;  ///< N�mero de elementos en la table.

};

#endif 