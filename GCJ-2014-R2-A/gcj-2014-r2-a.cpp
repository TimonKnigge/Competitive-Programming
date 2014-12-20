#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){

	// Formalities
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t){

		// Read input
		int N, X;
		cin >> N >> X;

		vector<int> fileSize(N);
		
		for (int i = 0; i < N; ++i){
			cin >> fileSize[i];
		}

		sort(fileSize.begin(), fileSize.end());

		int discs = 0, l = fileSize.size() - 1, skipped = 0;

		// Files are sorted in ascending order: try matching smallest
		// file with largest file.
		for (int i = 0; i < fileSize.size(); ++i){

			// When large and small files meet in the middle:
			// the rest of the files (to the right) all have
			// to go on seperate discs.
			if (l <= i){
				discs += (l == i ? 1 : 0) + skipped;
				break;
			}

			// Match [i] with a potential [l]
			while ((fileSize[i] + fileSize[l] > X) && (i + 1 < l)){
				--l;
				skipped++;
			}

			// If we matched this file with a larger one: remove
			// the larger file as well
			++discs;
			if (fileSize[i] + fileSize[l] <= X)
				--l;
		}

		cout << "Case #" << t << ": " << discs << endl;
	}

	return 0;
}