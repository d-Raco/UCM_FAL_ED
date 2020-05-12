#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <math.h>

const int MAX = 11;

template <class A>
class Polynomial {
public:
	Polynomial(A* vector, int degree);

	int Degree() const;
	A Coef(int index) const;
	Polynomial operator+(const Polynomial& other);
	A Evaluate(A x);

	//~Polynomial(); //destructor

private:
	A* _vector;
	int _degree;
};

template <class A>
Polynomial<A>::Polynomial(A* vector, int degree) {
	_vector = new A[MAX];
	for (int i = 0; i <= degree; i++) {
		_vector[i] = vector[i];
	}
	_degree = degree;
}

template <class A>
int Polynomial<A>::Degree() const {
	return _degree;
}

template <class A>
A Polynomial<A>::Coef(int index) const {
	if (index >= MAX) {
		return 0;
	}
	else {
		return _vector[index];
	}
}

template <class A>
Polynomial<A> Polynomial<A>::operator+(const Polynomial& other) {
	A* sum = new A[MAX];
	int aux = 0;
	for (int i = 0; i < MAX; ++i) {
		sum[i] = 0;
	}
	for (int i = 0; i <= other.Degree(); i++) {
		sum[i] = other.Coef(i);
	}
	for (int i = 0; i <= _degree; ++i) {
		sum[i] += _vector[i];
	}
	if (_degree > other.Degree())
		aux = _degree;
	else
		aux = other.Degree();
	Polynomial<A> addition = Polynomial<A>(sum, aux);
	return addition;
}

template <class A>
A Polynomial<A>::Evaluate(A x) {
	A sum = 0;
	for (int i = 0; i <= _degree ; i++) {
		sum = sum + (pow(x, i) * _vector[i]);
	}
	return sum;
}
/*
template <class A>
Polynomial<A>::~Polynomial() {
	delete _vector;
}
*/
#endif
