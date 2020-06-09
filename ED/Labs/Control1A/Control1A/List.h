/**
  @file List.h

  Implementation of ADT list using double-linked lists.
  
  Data Structures
  Facultad de Inform?tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G?mez Mart?n, 2012
*/
#ifndef __LIST_H
#define __LIST_H

#include "Exceptions.h"
#include <cassert>

/**
  Implementation of ADT list using double-linked lists.

 @author Marco Antonio G?mez Mart?n
 */
template <class T>
class List {
private:
	/**
	 Node for double-linked lists
	 */
	class Node {
	public:
		Node() : _next(NULL), _prev(NULL) {}
		Node(const T& elem) : _elem(elem), _next(NULL), _prev(NULL) {}
		Node(Node* ant, const T& elem, Node* sig) :
			_elem(elem), _next(sig), _prev(ant) {}

		T _elem;
		Node* _next;
		Node* _prev;
	};

public:

	/** -builder of an empty list */
	List() : _first(NULL), _last(NULL), _numElems(0) {}

	/** Destroyer */
	~List() {
		freeList();
	}

	/**
	 Adds an element at the beginning of the list.
	*/
	void push_front(const T& elem) {
		_first = insertElem(elem, NULL, _first);
		if (_last == NULL)
			_last = _first;
	}

	/**
	Adds an element at the end of the list
	*/
	void push_back(const T& elem) {
		_last = insertElem(elem, _last, NULL);
		if (_first == NULL)
			_first = _last;
	}

	/**
	 It returns the first element
	 */
	const T& front() const {
		if (empty())
			throw EEmptyList();
		return _first->_elem;
	}

	/**
	It returns the last element of the list
	 */
	const T& back() const {
		if (empty())
			throw EEmptyList();

		return _last->_elem;
	}

	/**
	 It removes the first element of the list
	*/
	void pop_front() {
		if (empty())
			throw EEmptyList();

		Node* nodeToDelete = _first;
		_first = _first->_next;
		removeElem(nodeToDelete);
		if (_first == NULL)
			_last = NULL;
	}

	/**
	It removes the last element of the list
	*/
	void pop_back() {
		if (empty())
			throw EEmptyList();

		Node* nodeToDelete = _last;
		_last = _last->_prev;
		removeElem(nodeToDelete);
		if (_last == NULL)
			_first = NULL;
	}

	/**
	It determines whether the list is empty
	 */
	bool empty() const {
		return _first == NULL;
	}

	/**
	 It returns the number o elements
	 */
	unsigned int numElems() const {
		return _numElems;
	}

	/**
	 It returns the i-th element of the list, starting 
	 to count on zero.
	 */
	const T& elem(unsigned int idx) const {
		if (idx >= _numElems)
			throw EInvalidAccess();

		Node* aux = _first;
		for (int i = 0; i < idx; ++i)
			aux = aux->_next;

		return aux->_elem;
	}

	/**
	 Internal class for implementing iterators that
	 can go through lists without changing them.
	 */
	class Iterator {
	public:
		void next() {
			if (_curr == NULL) throw EInvalidAccess();
			_curr = _curr->_next;
		}

		const T& elem() const {
			if (_curr == NULL) throw EInvalidAccess();
			return _curr->_elem;
		}

		bool operator==(const Iterator& other) const {
			return _curr == other._curr;
		}

		bool operator!=(const Iterator& other) const {
			return !(this->operator==(other));
		}
	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class List;

		Iterator() : _curr(NULL) {}
		Iterator(Node* act) : _curr(act) {}

		// Puntero al nodo actual del recorrido
		Node* _curr;
	};

	/**
	Internal class for iterators that can go through
	the list elements and change their values
	 */
	class MutableIterator {
	public:
		void next() {
			if (_curr == NULL) throw EInvalidAccess();
			_curr = _curr->_next;
		}

		const T& elem() const {
			if (_curr == NULL) throw EInvalidAccess();
			return _curr->_elem;
		}

		void setElem(const T& elem) {
			if (_curr == NULL) throw EInvalidAccess();
			_curr->_elem = elem;
		}

		bool operator==(const MutableIterator& other) const {
			return _curr == other._curr;
		}

		bool operator!=(const MutableIterator& other) const {
			return !(this->operator==(other));
		}
	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class List;

		MutableIterator() : _curr(NULL) {}
		MutableIterator(Node* act) : _curr(act) {}

		// Puntero al nodo actual del recorrido
		Node* _curr;
	};

	/**
	 It returs an iterator at the beginning of the list.
	 The 'c' refers to "constant" because it uses non-mutable
	 iterators.
	 */
	Iterator cbegin() const {
		return Iterator(_first);
	}

	/**
	Returns an iterator at the end of the list
	*/
	Iterator cend() const {
		return Iterator(NULL);
	}

	/**
	 It returns a mutable iterator at the beginning
	 of the list
	 */
	MutableIterator begin() {
		return MutableIterator(_first);
	}

	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de ?ste).
	 */
	MutableIterator end() const {
		return MutableIterator(NULL);
	}


	/**
	It removes the element pointed by the iterator.
	This iterator becomes invalid, but the returned 
	iterator is valid and points to the next element.
	 */
	MutableIterator remove(const MutableIterator& it) {
		if (it._curr == NULL)
			throw EInvalidAccess();

		// Cubrimos los casos especiales donde
		// borramos alguno de los extremos
		if (it._curr == _first) {
			pop_front();
			return MutableIterator(_first);
		}
		else if (it._curr == _last) {
			pop_back();
			return MutableIterator(NULL);
		}
		else {
			// El elemento a borrar es interno a la lista.
			Node* next = it._curr->_next;
			removeElem(it._curr);
			return MutableIterator(next);
		}
	}

	/**
	It inserts an element right before the element
	pointed by the iterator.
	If the iterator is at the end, then the element 
	will be added at the end of the list, and the
	iterator will still point outside the list.
	 */
	void insert(const T& elem, const MutableIterator& it) {

		// Special case at the beginning
		if (_first == it._curr) {
			push_front(elem);
		}
		else
			// Special case at the end
			if (it._curr == NULL) {
				push_back(elem);
			}
		// Caso normal
			else {
				insertElem(elem, it._curr->_prev, it._curr);
			}
	}


	/** Copy Builder */
	List(const List<T>& other) : _first(NULL), _last(NULL) {
		copy(other);
	}

	/** Operador de asignaci?n */
	List<T>& operator=(const List<T>& other) {
		if (this != &other) {
			freeList();
			copy(other);
		}
		return *this;
	}

	/** Operador de comparaci?n. */
	bool operator==(const List<T>& rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Node* p1 = _first;
		Node* p2 = rhs._first;
		while ((p1 != NULL) && (p2 != NULL)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_next;
			p2 = p2->_next;
		}

		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const List<T>& rhs) const {
		return !(*this == rhs);
	}


protected:

	void freeList() {
		freeNode(_first);
		_first = NULL;
		_last = NULL;
	}

	void copy(const List<T>& other) {
		_first = 0;
		_numElems = 0;

		Node* curr = other._first;
		while (curr != NULL) {
			push_back(curr->_elem);
			curr = curr->_next;
		}
	}

private:


	/**
	 Insert an element between two nodes
	*/
	Node* insertElem(const T& e, Node* node1, Node* node2) {
		Node* newNode = new Node(node1, e, node2);
		if (node1 != NULL)
			node1->_next = newNode;
		if (node2 != NULL)
			node2->_prev = newNode;
		_numElems++;
		return newNode;
	}

	/**
	 It removes a node updating previous and next nodes
	 if any.
	*/
	void removeElem(Node* n) {
		assert(n != NULL);
		Node* prev = n->_prev;
		Node* next = n->_next;
		if (prev != NULL)
			prev->_next = next;
		if (next != NULL)
			next->_prev = prev;
		_numElems--;
		delete n;
	}

	/**
	 It deletes this node and all the ones
	 linked after this
	 */
	static void freeNode(Node* first) {
		assert(!first || !first->_prev);

		while (first != NULL) {
			Node* aux = first;
			first = first->_prev;
			delete aux;
		}
	}

	// Puntero al primer y ?ltimo elemento
	Node* _first, * _last;

	// N?mero de elementos (n?mero de nodos entre _first y _last)
	unsigned int _numElems;
};

#endif // __LISTA_ENLAZADA_H