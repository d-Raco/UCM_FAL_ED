#include <iostream>
#include <string>
#include <fstream>
#include "BarsCompany.h"
#include "ListToString.h"
using namespace std;

/* Template for the Exam about Bars, for both exam models A and B.
This file does not need to be changed */
bool solveCase() {
	string op, s, m;
	int n;
	cin >> op;
	BarsCompany bc = BarsCompany();
	bool ret = op.compare("end");
	while (op.compare("end")) {
		if (!op.compare("addBar")) {
			cin >> s;
			bc.addBar(s);
		}
		else if (!op.compare("addDrink")) {
			cin >> s >> m >> n;
			bc.addDrink(s, m, n);
		}
		else if (!op.compare("consumeDrink")) {
			cin >> s >> m >> n;
			bc.consumeDrink(s, m, n);
		}
		else if (!op.compare("firstDrinks")) {
			cin >> s >> n;
			cout << listToStringCommas(bc.firstDrinks(s, n)) << endl;
		}
		else if (!op.compare("bars")) {
			cout << listToStringCommas(bc.bars()) << endl;
		}
		else if (!op.compare("bottles")) {
			cin >> s >> m;
			cout << bc.bottles(s, m) << endl;
		}
		cin >> op;
	}
	return ret;
}

int main()
{
	while (solveCase()){}
}
