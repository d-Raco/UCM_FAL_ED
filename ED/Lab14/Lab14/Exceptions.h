/*
  Implementation of exceptions needed for TADs.

 (c) Marco Antonio G?mez Mart?n, 2012
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
 Excepci?n generada por algunas operaciones de las pilas.
 */
DEFINE_EXCEPTION(EPilaVacia);

/**
 Excepci?n generada por algunas operaciones de las pilas.
 */
DEFINE_EXCEPTION(EPilaLlena);

/**
 Excepci?n generada por algunas de las operaciones de las colas.
 */
DEFINE_EXCEPTION(EEmptyQueue);

/**
 Excepci?n generada por algunas operaciones de las colas dobles.
 */
DEFINE_EXCEPTION(EDColaVacia);

/**
 Excepci?n generada por algunas operaciones de las listas.
 */
DEFINE_EXCEPTION(EEmptyList);

/**
 Excepci?n generada por accesos incorrectos a las listas
 (tanto a un n?mero de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DEFINE_EXCEPTION(EInvalidAccess);

/* For empty trees*/
DEFINE_EXCEPTION(EEmptyTree);
DEFINE_EXCEPTION(EWrongKey);
/* Generic Ones*/
DEFINE_EXCEPTION(EEmpty);


#endif // __EXCEPCIONES_H

