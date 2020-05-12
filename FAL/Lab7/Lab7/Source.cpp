#include <iostream>
using namespace std;

const int N = 10, MAXLength = 100;

const char rght = 'r', down = 'd', lft = 'l', up = 'u';

void mark(int column, int row, bool alreadyChecked[][N]) {
	alreadyChecked[column][row] = true;
}

void unmark(int column, int row, bool alreadyChecked[][N]) {
	alreadyChecked[column][row] = false;
}

void FindShortestPathOfOddNumbers(int matrix[][N], char bestPath[], char Path[], int dim, int &counterBestPath, int counterPath, int column, int row, bool alreadyChecked[][N]) {
	
	if (row == dim - 1 && column == dim - 1) {
		if (counterPath < counterBestPath) {
			counterBestPath = counterPath;
			for (int i = 0; i < counterBestPath; ++i) {
				bestPath[i] = Path[i];
			}
		}
	}
	else {
		if (column + 1 < dim) {/*down*/
			if (!alreadyChecked[column + 1][row] && matrix[column + 1][row] % 2 != 0) {
				Path[counterPath] = down;
				mark(column + 1, row, alreadyChecked);
				FindShortestPathOfOddNumbers(matrix, bestPath, Path, dim, counterBestPath, counterPath + 1, column + 1, row, alreadyChecked);
				unmark(column + 1, row + 1, alreadyChecked);
			}
		}
		if (column - 1 >= 0) {/*up*/
			if (!alreadyChecked[column - 1][row] && matrix[column - 1][row] % 2 != 0) {
				Path[counterPath] = up;
				mark(column - 1, row, alreadyChecked);
				FindShortestPathOfOddNumbers(matrix, bestPath, Path, dim, counterBestPath, counterPath + 1, column - 1, row, alreadyChecked);
				unmark(column - 1, row, alreadyChecked);
			}
		}
		if (row - 1 >= 0) {/*left*/
			if (!alreadyChecked[column][row - 1] && matrix[column][row - 1] % 2 != 0) {
				Path[counterPath] = lft;
				mark(column, row - 1, alreadyChecked);
				FindShortestPathOfOddNumbers(matrix, bestPath, Path, dim, counterBestPath, counterPath + 1, column, row - 1, alreadyChecked);
				unmark(column, row - 1, alreadyChecked);
			}
		}
		if (row + 1 < dim) {/*right*/
			if (!alreadyChecked[column][row + 1] && matrix[column][row + 1] % 2 != 0) {
				Path[counterPath] = rght;
				mark(column, row + 1, alreadyChecked);
				FindShortestPathOfOddNumbers(matrix, bestPath, Path, dim, counterBestPath, counterPath + 1, column, row + 1, alreadyChecked);
				unmark(column, row + 1, alreadyChecked);
			}
		}
	}
}

int main() {
	int dimension, lengthBestPath = MAXLength - 1;
	int matrix[N][N];
	bool booleans[N][N];
	char * bestPath, * Path;

	while (cin >> dimension && (dimension!= -1 || dimension <= 10)) {
		bestPath = new char[MAXLength];
		Path = new char[MAXLength];
		for (int i = 0; i < dimension; ++i) {
			for (int j = 0; j < dimension; ++j) {
				cin >> matrix[i][j];
				booleans[i][j] = false;
			}
		}
		booleans[0][0] = true;
		FindShortestPathOfOddNumbers(matrix, bestPath, Path, dimension, lengthBestPath, 0, 0, 0, booleans);
		if(lengthBestPath != 99) {
			//Print best path solution
			cout << bestPath[0];
			for (int i = 1; i < lengthBestPath; i++) {
				cout << " " << bestPath[i];
			}
			cout << endl;
		}
		else {
			cout << "IMPOSSIBLE" << endl;
		}
	}
	return 0;
}