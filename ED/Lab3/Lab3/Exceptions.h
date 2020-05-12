/*
  Implementation of exceptions needed for TADs.

 (c) Marco Antonio G�mez Mart�n, 2012
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
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepci�n generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaVacia);

/**
 Excepci�n generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EPilaLlena);

/**
 Excepci�n generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EColaVacia);

/**
 Excepci�n generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EDColaVacia);

/**
 Excepci�n generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EListaVacia);

/**
 Excepci�n generada por accesos incorrectos a las listas
 (tanto a un n�mero de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(EAccesoInvalido);

#endif // __EXCEPCIONES_H
