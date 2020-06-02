#pragma once

/*
  Implementation of exceptions needed for TADs.

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <string>
#include <iosfwd>
/**
 Parent class of all exceptions for the inheritance of error message
 */
class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string& msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }

	friend std::ostream& operator<<(std::ostream& out, const ExcepcionTAD& e);

protected:
	std::string _msg;
};

inline std::ostream& operator<<(std::ostream& out, const ExcepcionTAD& e) {
	out << e._msg;
	return out;
}


// Macro for declaring exceptions for not repeating the same over and over
#define DEFINE_EXCEPTION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DEFINE_EXCEPTION(EPilaVacia);

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DEFINE_EXCEPTION(EPilaLlena);

/**
 Excepción generada por algunas de las operaciones de las colas.
 */
DEFINE_EXCEPTION(EEmptyQueue);

/**
 Excepción generada por algunas operaciones de las colas dobles.
 */
DEFINE_EXCEPTION(EDColaVacia);

/**
 Excepción generada por algunas operaciones de las listas.
 */
DEFINE_EXCEPTION(EEmptyList);

/**
 Excepción generada por accesos incorrectos a las listas
 (tanto a un número de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DEFINE_EXCEPTION(EInvalidAccess);

/* For empty trees*/
DEFINE_EXCEPTION(EEmptyTree);
DEFINE_EXCEPTION(EWrongKey);

#endif // __EXCEPCIONES_H


