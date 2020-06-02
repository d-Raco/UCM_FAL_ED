/**
 @file Hash.h
 
 Declaration and implementation of localization functions for
 basic types and generic function that rely on the existence
 of the class hash method.
 
 Data Structure and Algorithms
 Faculty of Informatics
 Complutense University of Madrid
 
 (c) Antonio S�nchez Ruiz-Granados, 2012
 */

#ifndef __HASH_H
#define __HASH_H

#include <string>

// ----------------------------------------------------
//
// Funciones hash para distintos tipos de datos b�sicos
//
// ----------------------------------------------------


inline unsigned int hash(unsigned int key) {
	return key;
}

inline unsigned int hash(int key) {
	return (unsigned int) key;
}

inline unsigned int hash(char key) {
	return key;
}

// Note: This hash function for strings is not very good.
inline unsigned int hash(std::string key) {
	
	// Add up the ASCII values of all your characters.
	unsigned int valor = 0;
	for (unsigned int i=0; i<key.length(); ++i) {
		valor += key[i];
	}
	return valor;
}


/**
 * Funci�n hash gen�rica para clases que implementen un
 * m�todo publico hash.
 */
template<class C>
unsigned int hash(const C &key) {
	return key.hash();
}


#endif // __HASH_H