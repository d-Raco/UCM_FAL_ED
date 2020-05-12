//#pragma once
/**
  @file StackLL.h

  Implementation of the stack ADT with Linked Lists.
  */
#ifndef __STACKLL_H
#define __STACKLL_H

#include "Exceptions.h"

  /**
   Implementation of the stack ADT with Linked Lists.
   @author Marco Antonio G�mez Mart�n
   */
template <class T>
class StackLL {
public:

	/** Builder of an empty stack */
	StackLL() : _top(NULL), _numElems(0) {
	}

	/** Destroyer */
	~StackLL() {
		free();
		_top = NULL;
	}

	/* Add an element on the top*/
	void push(const T& elem) {
		_top = new Node(elem, _top);
		_numElems++;
	}

	/**
	 Remove the top from the stack
	*/
	void pop() {
		if (empty())
			throw EPilaVacia();
		Node* aBorrar = _top;
		_top = _top->_next;
		delete aBorrar;
		--_numElems;
	}

	/**
	 It returns the top (without modifying it)
	 */
	const T& top() const {
		if (empty())
			throw EPilaVacia();
		return _top->_elem;
	}

	/**
	 It determines if the stack is empty.
	 */
	bool empty() const {
		return _top == NULL;
	}

	/**
	 Returns the numbers of elements
	 */
	int numElems() const {
		return _numElems;
	}


	/** Copy builder */
	StackLL(const StackLL<T>& other) : _top(NULL) {
		copy(other);
	}

	/** Asignment operation*/
	StackLL<T>& operator=(const StackLL<T>& other) {
		if (this != &other) {
			free();
			copy(other);
		}
		return *this;
	}

	/** Comparator operator */
	bool operator==(const StackLL<T>& rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Node* cima1 = _top;
		Node* cima2 = rhs._top;
		while ((cima1 != NULL) && (cima2 != NULL)) {
			if (cima1->_elem != cima2->_elem)
				return false;
			cima1 = cima1->_sig;
			cima2 = cima2->_sig;
		}

		return (cima1 == NULL) && (cima2 == NULL);
	}

	bool operator!=(const StackLL<T>& rhs) const {
		return !(*this == rhs);
	}

protected:

	void free() {
		free(_top);
	}

	void copy(const StackLL& other) {

		if (other.empty()) {
			_top = NULL;
			_numElems = 0;
		}
		else {
			Node* act = other._top;
			Node* ant;
			_top = new Node(act->_elem);
			ant = _top;
			while (act->_sig != NULL) {
				act = act->_sig;
				ant->_sig = new Node(act->_elem);
				ant = ant->_sig;
			}
			_numElems = other._numElems;
		}
	}

private:

	/**
	Node class for the linked list implementation
	 */
	class Node {
	public:
		Node() : _next(NULL) {}
		Node(const T& elem) : _elem(elem), _next(NULL) {}
		Node(const T& elem, Node* next) :
			_elem(elem), _next(next) {}

		T _elem;
		Node* _next;
	};

	/**
	 Free all the nodes.
	 */
	static void free(Node* prim) {
		while (prim != NULL) {
			Node* aux = prim;
			prim = prim->_next;
			delete aux;
		}
	}

	/** Pointer to the top node */
	Node* _top;

	/** Number of elements */
	int _numElems;
};

#endif // __STACKLL_H
