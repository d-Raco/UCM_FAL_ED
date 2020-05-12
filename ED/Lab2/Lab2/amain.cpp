#include <iostream>
#include "Polynomial.h"
using namespace std;

int main() {
	int elem, valueX;
	int degree, cases;
	int* polynomialvector = new int[MAX];
	cin >> cases;
	while (cases--) {
		cin >> degree;
		for (int i = 0; i <= degree; ++i) {
			cin >> elem;
			polynomialvector[i] = elem;
		}
		Polynomial<int> polynom1 = Polynomial<int>(polynomialvector, degree);
		cin >> degree;
		for (int i = 0; i <= degree; ++i) {
			cin >> elem;
			polynomialvector[i] = elem;
		}
		Polynomial<int> polynom2 = Polynomial<int>(polynomialvector, degree);

		polynom1 = polynom1 + polynom2;
		cin >> valueX;
		cout << polynom1.Evaluate(valueX) << endl;
	}
	return 0;
}