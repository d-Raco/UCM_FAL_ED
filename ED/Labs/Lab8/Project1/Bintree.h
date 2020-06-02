/**
  @file Bintree.h

  Dynamic implementation of the Binary Tree TAD.

  Data Structure and Algorithms
  Faculty of Informatics
  Complutense University of Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __BINTREE_H
#define __BINTREE_H

#include "Exceptions.h"

#include "List.h" // Tipo devuelto por los recorridos

#include "Queue.h" // Tipo auxiliar para implementar el recorrido por levels

/**
  Dynamic implementation of TAD Bintree using
 nodes with a pointer to the left child and another to the
 right son. Implementation allows for sharing
 structure, keeping it under control by
 reference count. The implementation, however,
 is quite handmade, because in order not to complicate the code
 we avoid too much use of smart pointers,
 that automatically increase and decrease those
 references.

 @author Marco Antonio Gómez Martín
 */
template <class T>
class Bintree {
public:

	/** Builder; Operation EmptyTree */
	Bintree() : _root(NULL) {
	}

	/** Builder; operation with only root */
	Bintree(const T& elem) :
		_root(new Node(NULL, elem, NULL)) {
		_root->addRef();
	}

	/** Builder; operation Cons */
	Bintree(const Bintree& left, const T& elem, const Bintree& right) :
		_root(new Node(left._root, elem, right._root)) {
		_root->addRef();
	}

	/** Destroyer; eliminates the hierarchical node structure */
	~Bintree() {
		freeTree();
		_root = NULL;
	}

	/**
	 Returns the item stored in the root
	 */
	const T& root() const {
		if (empty())
			throw EEmptyTree();
		return _root->_elem;
	}

	/**
	 Returns a tree copy of the left tree.
	 This is a partial operation (failure with empty tree).
	*/
	Bintree leftChild() const {
		if (empty())
			throw EEmptyTree();

		return Bintree(_root->_left);
	}

	/**
	 Returns a tree copy of the right tree.
	 This is a partial operation (failure with empty tree).

	*/
	Bintree rightChild() const {
		if (empty())
			throw EEmptyTree();

		return Bintree(_root->_right);
	}

	/**
	 Observer operation that returns if the tree
	 is empty (contains no elements) or not.
	 */
	bool empty() const {
		return _root == NULL;
	}

	// //
	// TREE TRANSVERSALS
	// //

	List<T> preorder() const {
		List<T> ret;
		preorderAcu(_root, ret);
		return ret;
	}

	List<T> inorder() const {
		List<T> ret;
		inorderAcu(_root, ret);
		return ret;
	}

	List<T> postorder() const {
		List<T> ret;
		postorderAcu(_root, ret);
		return ret;
	}

	List<T> levels() const {

		if (empty())
			return List<T>();

		List<T> ret;
		Queue<Node*> toProcess;
		toProcess.push(_root);

		while (!toProcess.empty()) {
			Node* visit = toProcess.front();
			toProcess.pop();
			ret.ponDr(visit->_elem);
			if (visit->_iz)
				toProcess.push(visit->_iz);
			if (visit->_dr)
				toProcess.push(visit->_dr);
		}

		return ret;
	}

	// //
	// OTRAS OPERACIONES OBSERVADORAS
	// //

	/**
	 Returns the number of nodes in a tree.
	 */
	unsigned int numNodes() const {
		return numNodesAux(_root);
	}

	/**
	 It returns the depth of the tree.
	 */
	unsigned int depth() const {
		return depthAux(_root);
	}

	/**
	 Returns the number of leaves on a tree.
	 */
	unsigned int numLeaves() const {
		return numLeavesAux(_root);
	}

	/** Constructor copy */
	Bintree(const Bintree<T>& other) : _root(NULL) {
		copy(other);
	}

	/** Assignment Operator */
	Bintree<T>& operator=(const Bintree<T>& other) {
		if (this != &other) {
			freeTree();
			copy(other);
		}
		return *this;
	}

	/** Comparison operator. */
	bool operator==(const Bintree<T>& rhs) const {
		return compareAux(_root, rhs._root);
	}

	bool operator!=(const Bintree<T>& rhs) const {
		return !(*this == rhs);
	}

protected:

	/**
	 Node type that stores the element internally (type T),
	 and the pointers to the left son and the right son, like this
	 as the number of references there are.
	 */
	class Node {
	public:
		Node() : _left(NULL), _right(NULL), _numRefs(0) {}
		Node(Node* iz, const T& elem, Node* dr) :
			_elem(elem), _left(iz), _right(dr), _numRefs(0) {
			if (_left != NULL)
				_left->addRef();
			if (_right != NULL)
				_right->addRef();
		}

		void addRef() { assert(_numRefs >= 0); _numRefs++; }
		void remRef() { assert(_numRefs > 0); _numRefs--; }

		T _elem;
		Node* _left;
		Node* _right;

		int _numRefs;
	};

	/**
	 Protected constructor that creates a tree
	 from an existing hierarchical structure.
	 That hierarchical structure is SHARED, so
	 the reference is added.
	 It is used in leftChild and rightChild.
	 */
	Bintree(Node* raiz) : _root(raiz) {
		if (_root != NULL)
			_root->addRef();
	}

	void freeTree() {
		freeTree(_root);
	}

	void copy(const Bintree& other) {
		assert(this != &other);
		_root = other._root;
		if (_root != NULL)
			_root->addRef();
	}

	// //
	// AUXILIARY METHODS FOR TOURS
	// //

	static void preorderAcu(Node* ra, List<T>& acu) {
		if (ra == NULL)
			return;

		acu.push_back(ra->_elem);
		preorderAcu(ra->_left, acu);
		preorderAcu(ra->_right, acu);
	}

	static void inorderAcu(Node* ra, List<T>& acu) {
		if (ra == NULL)
			return;

		inorderAcu(ra->_left, acu);
		acu.push_back(ra->_elem);
		inorderAcu(ra->_right, acu);
	}

	static void postorderAcu(Node* ra, List<T>& acu) {
		if (ra == NULL)
			return;

		postorderAcu(ra->_left, acu);
		postorderAcu(ra->_right, acu);
		acu.push_back(ra->_elem);
	}

	// //
	// RECURSIVE METHODS FOR OTHER OPERATIONS
	// OBSERVERS
	// //

	static unsigned int numNodesAux(Node* ra) {
		if (ra == NULL)
			return 0;
		return 1 + numNodesAux(ra->_iz) + numNodesAux(ra->_dr);
	}

	static unsigned int depthAux(Node* ra) {
		if (ra == NULL)
			return 0;

		int leftDepth = depthAux(ra->_iz);
		int rightDepth = depthAux(ra->_dr);
		if (leftDepth > rightDepth)
			return 1 + leftDepth;
		else
			return 1 + rightDepth;
	}

	static unsigned int numLeavesAux(Node* ra) {
		if (ra == NULL)
			return 0;

		if ((ra->_iz == NULL) && (ra->_dr == NULL))
			return 1;

		return numLeavesAux(ra->_iz) + numLeavesAux(ra->_dr);
	}

private:

	/**
	 Remove all nodes of a tree structure
	 starting with the ra pointer.
	 The node is allowed to be NULL (there will be nothing
	 release).
	 */
	static void freeTree(Node* ra) {
		if (ra != NULL) {
			ra->remRef();
			if (ra->_numRefs == 0) {
				freeTree(ra->_left);
				freeTree(ra->_right);
				delete ra;
			}
		}
	}

	/**
	 It compares two hierarchical node structures,
	 given its roots (which may be NULL).
	 */
	static bool compareAux(Node* r1, Node* r2) {
		if (r1 == r2)
			return true;
		else if ((r1 == NULL) || (r2 == NULL))
			// En el if anterior nos aseguramos de
			// que r1 != r2. Si uno es NULL, el
			// otro entonces no lo será, luego
			// son distintos.
			return false;
		else {
			return (r1->_elem == r2->_elem) &&
				compareAux(r1->_left, r2->_right) &&
				compareAux(r1->_left, r2->_right);
		}
	}

protected:
	/**
	 Pointer to the root of the hierarchical structure
	 of nodes.
	 */
	Node* _root;
};

#endif // __BINTREE_H
