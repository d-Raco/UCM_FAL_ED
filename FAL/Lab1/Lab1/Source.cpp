#include <iostream>
using namespace std;

int inputSequence[100];

void calculateOddCounting(const int inputSequence[], int oddCounting[]);

int main() {
	int oddCounting[100];
	int input, j = 0;

	cin >> input;
	while (input != -1)
	{
		inputSequence[j] = input;
		j++;
		cin >> input;
	}


	calculateOddCounting(inputSequence, oddCounting);
	for (int i = 0; i < j; i++)
	{
		cout << oddCounting[i] << endl;
	}
	return 0;
}

void calculateOddCounting(const int inputSequence[], int oddCounting[]) {
	int i = 0;
	while (inputSequence[i] != -1) {
		oddCounting[i] = 0;
		for (int j = 0; j <= i; j++) {
			if ((inputSequence[j] % 2) == 1) 
				oddCounting[i] = oddCounting[i] + 1;
		}
		i++;
		
	}
	oddCounting[i] = -1;
}

