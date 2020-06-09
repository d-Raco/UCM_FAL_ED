#include <iostream>
#include "List.h"
#include "StackLL.h"
using namespace std;

//Ramón Costales de Ledesma

// This is the funtion to be implemented by the student
int solveCase(List<int> list) {
	List<int>::Iterator it = list.cbegin();
	StackLL<int> s = StackLL<int>();
	int sum = 0;

	while (it != list.cend()) {
		if (!s.empty() && s.top() == it.elem()) {
			s.pop();
			sum++;
		}
		else
			s.push(it.elem());
		it.next();
	}
	return sum;
}

// It reads a list of integers ended by -1 from the 
// the standard input
List<int> readList() {
	int elem;
	cin >> elem;
	List<int> list = List<int>();
	while (elem >= 0) {
		list.push_back(elem);
		cin >> elem;
	}
	return list;
}

// The main function for processing all the input cases 
// and providing the outputs
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		List<int> list = readList();
		int solution = solveCase(list);
		cout << solution << endl;
	}
}

