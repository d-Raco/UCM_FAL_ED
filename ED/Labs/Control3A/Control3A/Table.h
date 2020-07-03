/**
 @file TablaHash.h
 
 Implementation of the TAD Table using an open hash table
 
 Estructura de Datos y Algoritmos
 Facultad de Informática
 Universidad Complutense de Madrid
 
 (c) Antonio Sánchez Ruiz-Granados, 2012
 */
#ifndef __TABLE_H
#define __TABLE_H

#include "Exceptions.h"
#include "Hash.h"

#include <cassert>





// ---------------------------------------------
//
// TAD Table
//
// ---------------------------------------------




/**
 Implementation of the TAD Table using an open hash table
 
 Public operations follow:
 
 - Table: -> Table. Builder
 - insert: Table, Key, Value -> Table. Generator.
 - remove: Table, Key -> Table. Modifier.
 - exists: Table, Key -> Bool. Observer.
 - get: Table, Key - -> Value. Partial observer. 
 - empty: Table -> Bool. Observer.
 
 @author Antonio Sánchez Ruiz-Granados
 */
template <class C, class V>
class Table {
private:
	
	/**
	 * The table contains an array of pointers to nodes. Each node contains a 
	 * key, a value and a pointer to the next node.
	 */
	class Node {
	public:
		/* Builders. */
		Node(const C &key, const V &value) : 
				_key(key), _value(value), _next(NULL) {};
		
		Node(const C &key, const V &value, Node *next) : 
				_key(key), _value(value), _next(next) {};
		
		/* Atributos públicos. */
		C _key;    
		V _value;   
		Node *_next;  // Puntero al siguiente Node.
	};
	
public:
	
	/**
	 * Initial table size.
	 */
	static const int INITIAL_SIZE = 10;
	
	/**
	 * Default builder. Create a table with INITIAL_SIZE
	 * positions.
	 */
	Table() : _v(new Node*[INITIAL_SIZE]), _size(INITIAL_SIZE), _numElems(0) {
		for (unsigned int i=0; i<_size; ++i) {
			_v[i] = NULL;
		}
	}
	
	/**
	 * Destructor.
	 */
	~Table() {
		free();
	}
	
	/**
	 * insert a new pair (key, value) in the table. If there was
	 * an element with that key, its value is updated.
	 *
	 * @param key key of the new element.
	 * @param value value of the new element..
	 */
	void insert(const C &key, const V &value) {
		
		// If the occupation is very high, we extend the table
		float occupancy = 100 * ((float) _numElems) / _size; 
		if (occupancy > MAX_CAPACITY)
			extend();
		
		// We get the index associated with the key.
		unsigned int ind = ::hash(key) % _size;
		
		// If the key already existed, we updated its value
		Node *node = searchNode(key, _v[ind]);
		if (node != NULL) {
			node->_value = value;
		} else {
			// If the key didn't exist, we created a new Node and inserted it
			// in the beginning
			_v[ind] = new Node(key, value, _v[ind]);
			_numElems++;
		}
	}
	
	/**
	 * Remove the element from the table with the given key. If there was no
	 * element with this key, the table is not modified.
	 *
	 * @param key key of the element to be removed.
	 */
	void remove(const C &key) {
		
		// We get the index associated with the key.
		unsigned int ind = ::hash(key) % _size;
		
		// We look for the Node that contains that key and the previous Node.
		Node *curr = _v[ind];
		Node *prev = NULL;
		searchNode(key, curr, prev);
		
		if (curr != NULL) {
			
			// We took the node out of the node sequence.
			if (prev != NULL) {
				prev->_next = curr->_next;
			} else {
				_v[ind] = curr->_next;
			}
			
			// We delete the extracted Node.
			delete curr;
			_numElems--;
		}
	}
	
	/**
	 * Check if the table contains any element with the given key.
	 *
	 * @param key key to search.
	 * @return if there is an element with that key.
	 */
	bool exists(const C &key) {
		// We get the index associated with the key.
		unsigned int ind = ::hash(key) % _size;
		
		// We're looking for a node that contains that key.
		Node *Node = searchNode(key, _v[ind]);
		return Node != NULL;
	}
	
	/**
	 * Returns the value associated with the given key. If the table does not 
	 * contain that key throws up an exception.
	 *
	 * @param key key of the item to be searched.
	 * @return value associated with this key.
	 * @throw EWrongKey if the key does not exist on the table.
	 */
	V &get(const C &key) {
		
		// We get the index associated with the key.
		unsigned int ind = ::hash(key) % _size;
		
		// We're looking for a node that contains that key.
		Node *Node = searchNode(key, _v[ind]);
		if (Node == NULL)
			throw EWrongKey();
		
		return Node->_value;
	}

	/**
	 * Indicates if the table is empty, that is, if it does not contain any 
	 * item.
	 *
	 * @return if the table is empty.
	 */
	bool esVacia() const {
		return _numElems == 0;
	}
	
	/**
	 * Internal class that implements an iterator on the pair set
	 * (key, value). It is important to note that the iterator can
	 * return the pair set in any order.
	 */
	class Iterator {
	public:
		void next() {
			if (_curr == NULL) throw EInvalidAccess();
			
			// We are looking for the following Node from the list of Nodes.
			_curr = _curr->_next;
			
			// If we've reached the end of Nodes' list, we're still
			// searching by vector _v.
			while ((_curr == NULL) && (_ind < _table->_size - 1)) {
				++_ind;
				_curr = _table->_v[_ind];
			}
		}
		
		const C& key() const {
			if (_curr == NULL) throw EInvalidAccess();
			return _curr->_key;
		}
		
		const V& value() const {
			if (_curr == NULL) throw EInvalidAccess();
			return _curr->_value;
		}
		
		bool operator==(const Iterator &other) const {
			return _curr == other._curr;
		}
		
		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}
		
	private:
		// Para que pueda construir objetos del tipo iterador
		friend class Table;
		
		Iterator(const Table* table, Node* curr, unsigned int ind) 
			: _table(table), _curr(curr), _ind(ind) { }

		
		Node* _curr;				///< Pointer to current tour node
		unsigned int _ind;		///< Current index in vector _v
		const Table *_table;	///< Table that it is going through
	};
	
	/**
	 * Returns an iterator to the first pair (key, value) of the table. 
	 * The returned iterator will match end() if the table is empty.
	 * @return iterator pointing to the first (key, value) of the table.
	 */
	Iterator begin() {
		
		unsigned int ind = 0;
		Node* curr = _v[ind];
		
		while ((curr == NULL) && (ind < _size - 1)) {
			++ind;
			curr = _v[ind];
		}
		
		return Iterator(this, curr, ind);
	}
	
	/**
	 * Devuelve un iterador al final del recorrido (apunta más allá del último
	 * elemento de la table).
	 * @return iterador al final del recorrido.
	 */
	Iterator end() const {
		return Iterator(this, NULL, _size);
	}
	
	
	// 
	// METHODS THAT MAKE THE CLASS VERSATILE
	// 
	
	/**
	 * Builder to copy.
	 *
	*/
	Table(const Table<C,V> &other) {
		copy(other);
	}
	
	/**
	 * Assignment operator
	 *
	 * @param other table that you want to copy.
	 * @return reference to this same object (*this).
	 */
	Table<C,V> &operator=(const Table<C,V> &other) {
		if (this != &other) {
			free();
			copy(other);
		}
		return *this;
	}
	
	
private:
	
	// For the iterator to be able to access the private part
	friend class Iterator;
	
	/**
	 * free all the dynamic memory reserved for the table.
	 */
	void free() {
		
		// free the lists of nodes
		for (unsigned int i=0; i<_size; i++) {
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
	 * It makes a copy of the table it receives as a parameter. 
	 Before calling this method, the "free" method must be invoked.
	 *
	 * @param other table you want to copy.
	 */
	void copy(const Table<C,V> &other) {
		_size = other._size;
		_numElems = other._numElems;
	
		// Reservar memoria para el array de punteros a Nodes.
		_v = new Node*[_size];
		for (unsigned int i=0; i<_size; ++i) { 
			_v[i] = NULL;
			
			// Copy the list of Nodes from other._v[i] to _v[i].
			// The list of Nodes is reversed from the original.
			Node *curr = other._v[i];
			while (curr != NULL) {
				_v[i] = new Node(curr->_key, curr->_value, _v[i]); 
				curr = curr->_next;
			}
		}
	}
	
	/**
	 * This method doubles the capacity of the current array of pointers.
	 */
	void extend() {
		// We create a pointer to the current array and note its size.
		Node **vPrev = _v;
		unsigned int tamAnt = _size;

		// We duplicate the array in another memory location.
		_size *= 2; 
		_v = new Node*[_size];
		for (unsigned int i=0; i<_size; ++i)
			_v[i] = NULL;
		
		// We go through the original array by moving each Node to the new 
		// position in the new array.
		for (unsigned int i=0; i<tamAnt; ++i) {
			
			// IMPORTANT: Changing the size also changes the index
			// associated to each Node. That is, the Nodes are moved to
			// different in the new array.
			
			// NOTE: for efficiency we move the Nodes from the old array to the 
			// new, we don't create new Nodes. 
			
			// We go through the list of Nodes
			Node *node = vPrev[i];
			while (node != NULL) {
				Node *aux = node;
				node = node->_next;
				
				// We calculate the new index of the Node, we unhook it from 
				// old array and hook it up to the new one.
				unsigned int ind = ::hash(aux->_key) % _size;
				aux->_next = _v[ind];
				_v[ind] = aux;
			}
		}
		
		// We deleted the old array (it no longer contains any Nodes).
		delete[] vPrev;
	}
	
	/**
	 * Search for a Node from the Node "curr" that contains the given key. If you 
	 * find, "curr" will be pointed to that Node and "prev" to the previous Node.
	 * If it does not find it, "curr" will be pointed to NULL.
	 *
	 * @param key key to the Node you're looking for.
	 * @param curr [in/out] initially indicates the first Node of the search and 
	 * at the end indicates the Node found or NULL.
	 * @param prev [out] pointer to the Node before "curr" or NULL
	 */
	static void searchNode(const C &key, Node* &curr, Node* &prev) {
		prev = NULL;
		bool found = false;
		while ((curr != NULL) && !found) {
			
			// Check if the current Node contains the searched key
			if (curr->_key == key) {
				found = true;
			} else {
				prev = curr;
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
	static Node* searchNode(const C &key, Node* first) {
		Node *curr = first;
		Node *prev = NULL;
		searchNode(key, curr, prev);
		return curr;
	}
		
	/**
	 * Ocupación máxima permitida antes de ampliar la table en tanto por cientos.
	 */
	static const unsigned int MAX_CAPACITY = 80;
	
	
	Node **_v;               ///< Array de punteros a Node.
	unsigned int _size;       ///< Tamaño del array _v.
	unsigned int _numElems;  ///< Número de elementos en la table.
	

};

#endif // __TABLE_H