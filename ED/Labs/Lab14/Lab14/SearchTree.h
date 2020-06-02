/**
  @file SearchTree.h

  Dynamic implementation of the TAD Search Tree.

  Data Structure and Algorithms
  Faculty of Informatics
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __SEARCHTREE_H
#define __SEARCHTREE_H

#include "Exceptions.h"

#include "List.h" 

#include "StackLL.h" 

/**
 Dynamic implementation of TAD SearchTree using
 nodes with a pointer to the left child and another to the
 right son.

 

 @author Marco Antonio G�mez Mart�n
 */
template <class Key, class Value>
class SearchTree {
private:
	/**
	 Node type that stores the pair internally (key, value)
	 and the pointers to the left son and the right son.
	 */
	class Node {
	public:
		Node() : _lf(NULL), _rg(NULL) {}
		Node(const Key &clave, const Value &valor) 
			: _key(clave), _value(valor), _lf(NULL), _rg(NULL) {}
		Node(Node *iz, const Key &clave, const Value &valor, Node *dr)
			: _key(clave), _value(valor), _lf(iz), _rg(dr) {}

		Key _key;
		Value _value;
		Node *_lf;
		Node *_rg;
	};

public:

	/** Builder for Empty Tree */
	SearchTree() : _rt(NULL) {
	}

	/** Destructor; elimina la estructura jer�rquica de nodos. */
	~SearchTree() {
		free();
		_rt = NULL;
	}

	/**
	 Generating operation that adds a new key/value
	 to a search tree.
	 @param key New key.
	 @param value Value associated with that key. If the key
	 had already been inserted previously, it replaces the
	 old value with the new one.
	 */
	void insert(const Key &key, const Value &value) {
		_rt = insertAux(key, value, _rt);
	}

	/**
	 Modifying operation that removes a key from the tree.
	 If the key did not exist, the operation has no effect.

	 @param key key to be removed.
	 */
	void remove(const Key &key) {
		_rt = removeAux(_rt, key);
	}

	/**
	 Observer operation that returns the associated value
	 to a given key.

	 @param key Key you are retrieving information about it.
	 */
	const Value &get(const Key &clave) {
		Node *p = searchAux(_rt, clave);
		if (p == NULL)
			throw EWrongKey();

		return p->_value;
	}

	/**
	 Observer operation that allows to find out if a key
	 exists search tree.

	 @param key Key one is asking about.
	 */
	bool exists(const Key &clave) {
		return searchAux(_rt, clave) != NULL;
	}

	/**
	 Observer operation that returns if the tree
	 is empty (contains no elements) or not.


	 */
	bool empty() const {
		return _rt == NULL;
	}

	// //
	// OPERATIONS RELATED WITH INTERATORS
	// //

	/**
	 Internal class that implements an iterator on
	 the list that allows you to browse the list and even
	 alter the value of its elements.
	 */
	class Iterator {
	public:
		void next() {
			if (_curr == NULL) throw EInvalidAccess();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_curr->_rg)
				_curr = firstInOrder(_curr->_rg);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya est� vac�a, no quedan
				// ascendientes por visitar
				if (_antecessors.empty())
					_curr = NULL;
				else {
					_curr = _antecessors.top();
					_antecessors.pop();
				}
			}
		}

		const Key &key() const {
			if (_curr == NULL) throw EInvalidAccess();
			return _curr->_key;
		}

		const Value &value() const {
			if (_curr == NULL) throw EInvalidAccess();
			return _curr->_value;
		}

		bool operator==(const Iterator &other) const {
			return _curr == other._curr;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}
	protected:
		// So that I can build objects from the
		// iterator type
		friend class SearchTree;

		Iterator() : _curr(NULL) {}
		Iterator(Node *curr) {
			_curr = firstInOrder(curr);
		}

		/**
		 Busca el primer elemento en inorden de
		 la estructura jer�rquica de nodos pasada
		 como par�metro; va apilando sus ascendientes
		 para poder "ir hacia atr�s" cuando sea necesario.
		 @param p Puntero a la ra�z de la subestructura.
		 */
		Node *firstInOrder(Node *p) {
			if (p == NULL)
				return NULL;

			while (p->_lf != NULL) {
				_antecessors.push(p);
				p = p->_lf;
			}
			return p;
		}

		// Pointer to current trip node
		// NULL if we've reached the end.
		Node* _curr;

		// Ascendants of the current node
		// still to be visited
		StackLL<Node*> _antecessors;
	};
	
	/**
	 Return the iterator to the top of the list.
	 @return iterator to the top of the list;
	 will match end() if the list is empty.
	 */
	Iterator begin() {
		return Iterator(_rt);
	}

	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de �ste).
	 */
	Iterator end() const {
		return Iterator(NULL);
	}


	// //
	// METHODS THAT MAKE THIS CLASS MORE USABLE FOR COPIES AND ASSIGNMENT
	// //

	/** Constructor copy */
	SearchTree(const SearchTree<Key, Value> &other) : _rt(NULL) {
		copy(other);
	}

	/** Operador de asignaci�n */
	SearchTree<Key, Value> &operator=(const SearchTree<Key, Value> &other) {
		if (this != &other) {
			free();
			copy(other);
		}
		return *this;
	}

protected:

	/**
	 Constructor protegido que crea un �rbol
	 a partir de una estructura jer�rquica de nodos
	 previamente creada.
	 Se utiliza en hijoIz e hijoDr.
	 */
	SearchTree(Node *root) : _rt(root) {
	}

	void free() {
		free(_rt);
	}

	void copy(const SearchTree &other) {
		_rt = copyAux(other._rt);
	}

private:

	/**
	 Remove all nodes of a tree structure
	 starting with the rt pointer.
	 The node is allowed to be NULL (there will be nothing
	 release).
	 */
	static void free(Node *rt) {
		if (rt != NULL) {
			free(rt->_lf);
			free(rt->_rg);
			delete rt;
		}
	}

	/**
	 Copies the hierarchical node structure past
	 as a parameter (pointer to its root) and returns a
	 pointer to a new hierarchical structure, copy
	 of previous (and therefore to be released).
	 */
	static Node *copyAux(Node *rt) {
		if (rt == NULL)
			return NULL;

		return new Node(copyAux(rt->_lf),
						rt->_key, rt->_value,
						copyAux(rt->_rg));
	}

	/**
	 Insert a pair (key, value) in the structure
	 hierarchical that begins at the pointer passed as a parameter.
	 That pointer is allowed to be NULL, so it will create
	 a new node that will become the new root of that
	 hierarchical structure. The method returns a pointer to the
	 root of the modified structure. Under normal conditions
	 will match the received parameter; it will only change if
	 the structure was empty.
	 */
	static Node *insertAux(const Key &key, const Value &value, Node *p) {

		if (p == NULL) {
			return new Node(key, value);
		} else if (p->_key == key) {
			p->_value = value;
			return p;
		} else if (key < p->_key) {
			p->_lf = insertAux(key, value, p->_lf);
			return p;
		} else { // (key > p->_key)
			p->_rg = insertAux(key, value, p->_rg);
			return p;
		}
	}

	/**
	 Busca una key en la estructura jer�rquica de
	 nodos cuya ra�z se pasa como par�metro, y devuelve
	 el nodo en la que se encuentra (o NULL si no est�).
	 @param p Puntero a la ra�z de la estructura de nodos
	 @param key Key a buscar
	 */
	static Node *searchAux(Node *p, const Key &key) {
		if (p == NULL)
			return NULL;

		if (p->_key == key)
			return p;

		if (key < p->_key)
			return searchAux(p->_lf, key);
		else
			return searchAux(p->_rg, key);
	}

	/**
	 Removes (if any) the key/value from the hierarchical structure
	 of nodes pointed by p. If the key appeared in the root itself,
	 it will change, so the new root is returned. If it doesn't change
	 p. is returned

	 @param p Root of the hierarchical structure where to delete the key.
	 @param key Key to be deleted.
	 @return New root of the structure, after deleting. If the root
	 it does not change, it returns its own p.
	*/
	static Node* removeAux(Node *p, const Key &key) {

		if (p == NULL)
			return NULL;

		if (key == p->_key) {
			return removeRoot(p);
		} else if (key < p->_key) {
			p->_lf = removeAux(p->_lf, key);
			return p;
		} else { // key > p->_key
			p->_rg = removeAux(p->_rg, key);
			return p;
		}
	}

	/**
	 Deletes the root of the hierarchical node structure
	 and returns the pointer to the new root that guarantees
	 that the structure is still valid for a
	 search (ordered keys).
	 */
	static Node *removeRoot(Node *p) {

		Node *aux;

		// If there is no left child, the root becomes
		// the right child
		if (p->_lf == NULL) {
			aux = p->_rg;
			delete p;
			return aux;
		} else
			// If there is no right child, the root becomes
			// the left child
		if (p->_rg == NULL) {
			aux = p->_lf;
			delete p;
			return aux;
		} else {
			// We turn the smallest element of the right child
			// at the root.
			return moveMinAndRemove(p);
		}
	}

	/**
	 Auxiliary method for deletion; receives a pointer to the
	 root to be erased. Find the smallest element of the right child
	 which will become the root (which will return), remove the old
	 root (p) and "sews" all the pointers, so that now

	   - The minimum becomes the root, whose left son and
	     right were the left and right sons of the root
	     old.
	   - The left child of the parent of the smaller element
	     becomes the rightful former son of that minimum.
	 */
	static Node *moveMinAndRemove(Node *p) {

		// We go down until we find the element
		// smaller (the one without a left child).
		// We are also keeping the parent (which will be null
		// if the right child is directly the
		// smaller).
		Node *parent = NULL;
		Node *aux = p->_rg;
		while (aux->_lf != NULL) {
			parent = aux;
			aux = aux->_lf;
		}

		// aux points to the smallest element.
		// parent points to its parent (if the node is a left child)

		// Two cases depending on whether the parent of the node with 
		// the minimum is or is not the root to be eliminated
		// (=> parent != NULL)
		if (parent != NULL) {
			parent->_lf = aux->_rg;
			aux->_lf = p->_lf;
			aux->_rg = p->_rg;
		} else {
			aux->_lf = p->_lf;
		}

		delete p;
		return aux;
	}

	/** 
	 Pointer to the root of the hierarchical structure
	 of nodes.
	 */
	Node *_rt;
};

#endif // __Arbus_H