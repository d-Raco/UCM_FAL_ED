//joseignaciodg
//Rymond3
#include <iostream>
using namespace std;

const int MAX = 100;

int highestsum(int seq[], int size, int sumLength);

int main() {
	int sequence[MAX];
	int numSequences, size, elem, sumLength;

	cin >> numSequences;
	while (numSequences--) {
		cin >> size >> sumLength;
		for (int i = 0; i < size; ++i) {
			cin >> elem;
			sequence[i] = elem;
		}

		cout << highestsum(sequence, size, sumLength) << endl;
	}


	return 0;
}

//Invariant: I ≡ 0 ≤ size ≤ MAX ∧ 0 <= index < size - sumLength ∧ 0 <= sumLength <= size  ∧ index = (∃i, ∀j: (0 <= j < sumLength) ∧ (sum = Σj: 0 <= j < sumLength: sum = Σseq[j]) ∧ (0 <= i <= size - sumLength) ∧ (maxsum = Σi: i <= i + sumLength: Σseq[i]) : maxsum >= sum)

//Pre-Condition: { 0 <= size < MAX }
//               fun highestsum(int seq[], int size, int sumLength) return int index
int highestsum(int seq[], int size, int sumLength) {
	int sum = 0, maxsum = 0, index = 0, prev;

	prev = seq[0];
	for (int j = 0; j < sumLength; ++j) {
		sum += seq[j];
	}
	maxsum = sum;
	for (int i = 1; i <= size - sumLength; ++i) {
		sum += seq[i + sumLength - 1];
		sum -= prev;
		if (sum > maxsum) {
			maxsum = sum;
			index = i;
		}
		prev = seq[i];
	}
	return index;
}
//Post-Condition: index = (∃i, ∀j: (0 <= j < sumLength) ∧ (sum = Σj: 0 <= j < sumLength: sum = Σseq[j]) ∧ (0 <= i <= size - sumLength) ∧ (maxsum = Σi: i <= i + sumLength: Σseq[i]) : maxsum >= sum)

// Complexity of the execution time (n = size and l = sumLength)
//T(n) = tassign ·(5n - 4l + 2) + tcompare·(2n - l - 1) + tincrement ·(n - 1) + tretrieve ·(2n - l - 1) ∈ O(n, l) -> linear complexity
