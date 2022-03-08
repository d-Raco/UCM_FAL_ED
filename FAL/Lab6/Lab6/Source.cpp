/*
I14
joseignaciodg
Rymond3

Steps:
1. We considered implementing 2 pivots (first and last element) and a boolean which checks if the previous element of the sequence is even.
2. Also we decided to implement a variable in order to obtain the middle of each partition formed by the pivots. 
3. Then we implemented the recursion step.

COMPLEXITY:																							{ C0   if n = 0, 1, 2 ,3
2) k											|											| T(n)  {
3) k + DisruptionOfNumbers(seq, 0, n) = 2k		|											|		{ C1 + T(n/2)  if n > 3
10) k + DisruptionOfNumbers(seq, 0, n) = 5k		|	O(log n) -> logarithmic complexity		|
20) k + DisruptionOfNumbers(seq, 0, n) = 6k		|											|T(n) = C1 + T(n/2) = C1 + C1 + T((n/2)/2) = ... = C1*k +T(n/2^k)
...												|											|
100)k + DisruptionOfNumbers(seq, 0, n) = 9k		|											| n/2^k = 1 --> b = 2^k --> k = log2 n || C1*log n + TT(n/2^log2 n)∈ O(log n)
*/

#include <iostream>
using namespace std;

const int MAX = 200;

int DisruptionOfNumbers(int seq[], int first, int last) {
	int position, middle;
	bool isEven;

	middle = (first + last) / 2;
	if (seq[middle - 1] % 2 == 0) 
		isEven = true;
	else
		isEven = false;
	bool odd = seq[middle] % 2 != 0;

	if (odd && isEven)
		position = middle;
	else {
		if (odd)
			position = DisruptionOfNumbers(seq, first, middle - 1);
		else
			position = DisruptionOfNumbers(seq, middle + 1, last);
	}
	return position;
}

int main() {
	int numElem, element;
	int sequence[MAX];

	while (cin >> numElem && numElem != -1) {
		for (int i = 0; i < numElem; ++i) {
			cin >> element;
			sequence[i] = element;
		}
		cout << DisruptionOfNumbers(sequence, 0, numElem) << endl;
	}


	return 0;
}
