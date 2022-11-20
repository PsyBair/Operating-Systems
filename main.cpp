// Operating Systems Assignment 2 - Lorenzo Bair
// Banker's Algorithm

#include <iostream>

using namespace std;

int main() {
	int allocation[5][3] = { { 0, 1, 0 }, // Process0 
							 { 2, 0, 0 }, // 1
							 { 3, 0, 2 }, // 2
							 { 2, 1, 1 }, // 3
							 { 0, 0, 2 } }; // 4
	int max[5][3] = { { 7, 5, 3 }, // Process0
					  { 3, 2, 2 }, // 1
					  { 9, 0, 2 }, // 2
					  { 2, 2, 2 }, // 3
					  { 4, 3, 3 } }; // 4
	int available[3] = { 3, 3, 2 }; // Available Resources
	const int n = 5; // Number of processes
	const int m = 3; // Number of resources
	int i, j, k = 0; // Indices and loop variables

	int safeFlags[n], sequence[n], index = 0;
	for (k = 0; k < n; k++) {
		safeFlags[k] = 0;
	}

	int need[n][m];
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - allocation[i][j];
	}

	int x = 0;
	for (k = 0; k < 5; k++) {
		for (i = 0; i < n; i++) {
			if (safeFlags[i] == 0) {
				int flag = 0;
				for (j = 0; j < m; j++) {
					if (need[i][j] > available[j]) {
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					sequence[index++] = i;
					for (x = 0; x < m; x++)
						available[x] += allocation[i][x];
					safeFlags[i] = 1;
				}
			}
		}
	}

	bool safe = true;

	// Outputs if sequence is not safe
	for (int i = 0; i < n; i++) {
		if (safeFlags[i] == 0) {
			safe = false;
			cout << "Sequence is not safe!";
			break;
		}
	}

	// Outputs if sequence is safe
	if (safe == true) {
		cout << "SAFE Sequence: ";
		for (i = 0; i < (n - 1); i++)
			cout << "Process" << sequence[i] << " -> ";
		cout << "Process" << sequence[n - 1];
	}
}
