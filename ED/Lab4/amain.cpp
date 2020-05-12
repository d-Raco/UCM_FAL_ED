#include <iostream>
#include "Exceptions.h"
#include "Queue.h"
using namespace std;

int main() {
	Queue<int> list;
	int cases, numElem, elem, pos;

	cin >> cases;
	while (cases--) {
		cin >> numElem;
		for (int i = 0; i < numElem; ++i) {
			cin >> elem;
			list.push(elem);
		}
		cin >> pos;
		list.penalizeElem(pos);
		
		for(int i = 0; i < numElem; ++i) {
			cout << q.front() << " ";
			q.pop();
		}
		cout << endl;
	}
	return 0;
}