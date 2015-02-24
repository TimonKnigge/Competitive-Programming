#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> ii;

// We will be sorting blocks on the first coordinate,
// breaking ties using the second coordinate.
bool compare(ii l, ii r){
	if (l.first == r.first)
		return l.second < r.second;
	else return l.first < r.first;
}

int main(){

	while (true){ // silly input format :-(

		int n;
		cin >> n;

		if (n == 0){
			cout << '*' << endl;
			break;
		}

		// Retrieve input.
		vector<ii> blocks(n);
		for (int i = 0; i < n; i++){
			int l, m;
			cin >> l >> m;
			blocks[i] = ii(l, m);
		}

		sort(blocks.begin(), blocks.end(), compare);

		vector<int> lis(n);
		lis[0] = 1;

		// Summary: for each block i, check for each block j that is earlier in the sequence,
		// if we can extend the longest sequence ending in j using i.
		int maxLis = 1;
		for (int i = 1; i < n; i++){
			for (int j = 0; j < i; j++){
				if (blocks[j].second < blocks[i].second && lis[i] < lis[j] + 1){
					lis[i] = lis[j] + 1;
					maxLis = max(lis[i], maxLis);
				}
			}
		}

		cout << maxLis << endl;
	}

	return 0;
}