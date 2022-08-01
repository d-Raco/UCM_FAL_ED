//joseignaciodg
//d-Raco
#include <iostream>
using namespace std;

const int MAX = 100;

int logstSequence(int seq[], int size);

int main() {
	int sequence[MAX];
	int numSequences, size, elem;

	cin >> numSequences;
	while (numSequences--) {
		cin >> size;
		for (int i = 0; i < size; ++i) {
			cin >> elem;
			sequence[i] = elem;
		}

		cout << logstSequence(sequence, size) << endl;
	}


	return 0;
}

//Invariant: I ≡ 0 ≤ size ≤ MAX ∧ 0 <= count <= maxLength < size ∧ maxLength = (max(j - i) : ∃i, ∃j : (0 ≤ i <= j) ^ (i <= j < size) : ∀h: i <= h < j: seq[h] % 2 != 0) ∧ count = (j - i : ∃i, ∃j : (0 ≤ i <= j) ^ (i <= j < size) : ∀h: i <= h < j: seq[h] % 2 != 0)

//Pre-Condition: {0 <= size < MAX}
//               fun logstSequence(int seq[], int size) return int maxLength
int logstSequence(int seq[], int size) {
	int maxLength = 0, count = 0;
	
	for (int i = 0; i < size; i++) {
		if (seq[i] % 2 != 0) {
			count++;
			if (maxLength < count)
				maxLength = count;
		}
		else
			count = 0;
	}
	return maxLength;
}
//Post-Condition: maxLength = (max(j - i) : ∃i, ∃j : (0 ≤ i <= j) ^ (i <= j < size) : ∀h: i <= h < j: seq[h] % 2 != 0) 

// Complexity of the execution time
//T(n) = tassign ·(3 + n) + tcompare·(3n + 1) + tincrement ·(2n) + tretrieve ·(n) ∈ O(n) -> linear complexity
