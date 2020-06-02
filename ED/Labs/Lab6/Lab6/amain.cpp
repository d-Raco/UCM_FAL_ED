#include <iostream>
#include <string>
#include "StackLL.h"
using namespace std;

bool balanced(char e[100], int i);
bool isOpenning(char c);
bool isClosing(char c);
bool match(char c1, char c2);

int main() {
	string s;
	int i, cases;
	char expression[100];
	cin >> cases;
	while (cases--) {
		
		cin >> s;
		i = 0;
		while (i < s.size()) {
			expression[i] = s[i];
			++i;
		}
		if (balanced(expression, i)) {
			cout << "yes" << endl;
		}
		else {
			cout << "no" << endl;
		}

	}
	return 0;
}

bool balanced(char e[100], int n) {
	int i = 0;
	StackLL<char> thing;
	bool balance = true;

	while (i < n) {
		if (isOpenning(e[i])) {
			thing.push(e[i]);
		}
		else if (isClosing(e[i])) {
			if (thing.empty() || !match(thing.top(), e[i])) {
				return false;
			}
			else {
				thing.pop();
			}
		}
		++i;
	}
	return balance && thing.empty();
}

bool isOpenning(char c) {
	switch (c)
	{
	case '[':
	case '{':
	case '(':
		return true;
	default:
		return false;
	}
}

bool isClosing(char c) {
	switch (c)
	{
	case ']':
	case '}':
	case ')':
		return true;
	default:
		return false;
	}
}

bool match(char c1, char c2) {
	if (((c1 == '[') && (c2 == ']')) || ((c1 == '(') && (c2 == ')')) || ((c1 == '{') && (c2 == '}')))
	{
		return true;
	}
	else
		return false;
}