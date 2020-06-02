//#pragma once
/**
  @file StackLL.h

  Implementation of the stack ADT with Linked Lists.
  */
#ifndef __STACKLL_H
#define __STACKLL_H

#include "Exceptions.h"

  /**
   Implementaci�n del TAD Pila utilizando una lista enlazada de nodos.

   Las operaciones son:

   - PilaVacia: -> Pila. Generadora implementada en el
	 constructor sin par�metros.
   - push: Pila, Elem -> Pila. Generadora
   - pop: Pila - -> Pila. Modificadora parcial.
   - top: Pila - -> Elem. Observadora parcial.
   - empty: Pila -> Bool. Observadora.
   - numElems: Pila -> Entero. Observadora.

   @author Marco Antonio G�mez Mart�n
   */
template <class T>
class StackLL {
public:

	/** Constructor; operaci�n PilaVacia */
	StackLL() : _top(NULL), _numElems(0) {
	}

	/** Destructor; elimina la lista enlazada. */
	~StackLL() {
		free();
		_top = NULL;
	}

	/**
	 Apila un elemento. Operaci�n generadora.

	 @param elem Elemento a apilar.
	*/
	void push(const T& elem) {
		_top = new Node(elem, _top);
		_numElems++;
	}

	/**
	 Desapila un elemento. Operaci�n modificadora parcial,
	 que falla si la pila est� vac�a.

	 pop(Apila(elem, p) = p
	 error: pop(PilaVacia)
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
	 Devuelve el elemento en la top de la pila. Operaci�n
	 observadora parcial, que falla si la pila est� vac�a.

	 top(Apila(elem, p) = elem
	 error: top(PilaVacia)

	 @return Elemento en la top de la pila.
	 */
	const T& top() const {
		if (empty())
			throw EPilaVacia();
		return _top->_elem;
	}

	/**
	 Devuelve true si la pila no tiene ning�n elemento.

	 empty(PilaVacia) = true
	 empty(Apila(elem, p)) = false

	 @return true si la pila no tiene ning�n elemento.
	 */
	bool empty() const {
		return _top == NULL;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 pila.
	 numElems(PilaVacia) = 0
	 numElems(Apila(elem, p)) = 1 + numElems(p)

	 @return N�mero de elementos.
	 */
	int numElems() const {
		return _numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copy */
	StackLL(const StackLL<T>& other) : _top(NULL) {
		copy(other);
	}

	/** Operador de asignaci�n */
	StackLL<T>& operator=(const StackLL<T>& other) {
		if (this != &other) {
			free();
			copy(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
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
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podr�a ser NULL si
	 el nodo es el �ltimo de la lista enlazada.
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
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como par�metro.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar).
	 */
	static void free(Node* prim) {
		while (prim != NULL) {
			Node* aux = prim;
			prim = prim->_next;
			delete aux;
		}
	}

	/** Puntero al primer elemento */
	Node* _top;

	/** N�mero de elementos */
	int _numElems;
};

#endif
