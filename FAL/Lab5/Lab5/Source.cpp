/*The first instance was linear, so the judge didn´t accept it. Trying to search a logarithmic complexity we realised 1+2+3+4+5+6+7+8+9 = 45, so we used it to
reach a logarithmic solution. We kept having a timelimit because when we cin the number, we storte it inside an int, when it should be a long long int 

COMPLEXITY: (by recursive iterations)
1) k
2) k + SNN(n-1)				| n times) k * (num of digits of n) + SNN(last digit of n)
...									|
10) k + SNN(n/10) = 2k		|	O(log n) -> logarithmic complexity
11) k + SNN(n/10) = 2k		|
12) k + SNN(n/10) = 3k		|
...									|
100) k + SNN(n/10) = 3k	|
*/
#include <iostream>
using namespace std;

long long int SNN(long long int num) {
	if (num == 1 || num == 0) {
		return num;
	}

	if (num % 10 == 0) {
		return 45 * num / 10 + SNN(num / 10);
	}
	return num % 10 + SNN(num - 1);
}

int main() {
	long long int num;

	while (cin >> num && num != 0)
	{
		cout << SNN(num) << endl;
	}
	return 0;
}