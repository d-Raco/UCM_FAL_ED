#pragma once

/**
  @file Queue.h

  Queue ADT with linked list

  Data structures
  Facultad de Inform?tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G?mez Mart?n, 2012
*/
#ifndef __QUEUE_LINKED_LIST_H
#define __QUEUE_LINKED_LIST_H

#include "Exceptions.h"

/**
 @author Marco Antonio G?mez Mart?n
 */
template <class T>
class Queue {
public:

	/** Builder */
	Queue() : _first(NULL), _last(NULL), _numElems(0) {
	}

	/** Destructor. */
	~Queue() {
		freeQueue();
		_first = _last = NULL;
	}

	/**
	 Add an element to the end
	*/
	void push(const T& elem) {
		Node* newNode = new Node(elem, NULL);

		if (_last != NULL)
			_last->_next = newNode;
		_last = newNode;
		// Si la cola estaba vac?a, el primer elemento
		// es el que acabamos de a?adir
		if (_first == NULL)
			_first = newNode;
		_numElems++;
	}

	/**
	 Remove the first element
	*/
	void pop() {
		if (empty())
			throw EEmptyQueue();
		Node* toDelete = _first;
		_first = _first->_next;
		delete toDelete;
		--_numElems;
		// Si la cola se qued? vac?a, no hay
		// ?ltimo
		if (_first == NULL)
			_last = NULL;
	}

	/**
	 Return the first element of the queue (without removing it)
	 */
	const T& front() const {
		if (empty())
			throw EEmptyQueue();
		return _first->_elem;
	}

	/**
	 It determines whether the que is empty
	 */
	bool empty() const {
		return _first == NULL;
	}

	/**
	 Returns the number of elements
	 */
	int numElems() const {
		return _numElems;
	}


	/** Copy Constructor */
	Queue(const Queue<T>& other) : _first(NULL), _last(NULL) {
		copy(other);
	}

	/** Operador de asignaci?n */
	Queue<T>& operator=(const Queue<T>& other) {
		if (this != &other) {
			freeQueue();
			copy(other);
		}
		return *this;
	}

	/** Comparator operator */
	bool operator==(const Queue<T>& rhs) const {
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

	bool operator!=(const Queue<T>& rhs) const {
		return !(*this == rhs);
	}

protected:

	void freeQueue() {
		freeQueue(_first);
	}

	void copy(const Queue& other) {

		if (other.empty()) {
			_first = _last = NULL;
			_numElems = 0;
		}
		else {
			Node* act = other._first;
			Node* ant;
			_first = new Node(act->_elem);
			ant = _first;
			while (act->_next != NULL) {
				act = act->_next;
				ant->_next = new Node(act->_elem);
				ant = ant->_next;
			}
			_last = ant;
			_numElems = other._numElems;
		}
	}

private:

	/**
	Node class that stores an element with a pointer to the next node 
	(if any). The next pointer is null, if the contained element is
	the last one.
	 */
	class Node {
	public:
		Node() : _next(NULL) {}
		Node(const T& elem) : _elem(elem), _next(NULL) {}
		Node(const T& elem, Node* sig) :
			_elem(elem), _next(sig) {}

		T _elem;
		Node* _next;
	};

	/**
	 Removes all the nodes of the linked list,
	 whose first node is the parameter.
	 If the first node is NULL, then nothing is freed.
	 */
	static void freeQueue(Node* prim) {
		while (prim != NULL) {
			Node* aux = prim;
			prim = prim->_next;
			delete aux;
		}
	}

	/** Pointer to the first node */
	Node* _first;

	/** Pointer to the last node */
	Node* _last;

	/** Number of elements */
	int _numElems;
};

#endif // __QUEUE_LINKED_LIST_H