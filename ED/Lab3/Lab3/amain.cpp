#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

const string Centinel = "end";

int main() {
	int cases;
	string line;
	StackLL<int> stack;
	cin >> cases;
	while (cases--) {
		cin >> line;
		while (line.compare(Centinel)) {
			if (line[0] == '+') {
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(a + b);

			}
			else if (line[0] == '*') {
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(b * a);
			}
			else if (line[0] == '-') {
				int a = stack.top();
				stack.pop();
				int b = stack.top();
				stack.pop();
				stack.push(b - a);
			}
			else {
				stack.push(stoi(line));
			}
			cin >> line;
		} 
		cout << stack.top() << endl;
		stack.pop();
	}



	return 0;
}