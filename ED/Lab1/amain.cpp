#include "Circle.h"
#include <iostream>
using namespace std;

int main() {
	int numcases, x, y;
	Point left, right, point;
	Circle circle;

	cin >> numcases;
	while (numcases--) {
		cin >> x >> y;
		left.setValues(x, y);

		cin >> x >> y;
		right.setValues(x, y);

		cin >> x >> y;
		point.setValues(x, y);

		circle.setValues(left, right);
		
		cout << circle.area() << " ";
		if (circle.isInside(point))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
	return 0;
}