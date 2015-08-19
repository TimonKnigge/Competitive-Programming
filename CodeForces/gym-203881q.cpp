#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> optimal(145, 1000);
	vector<int> optleft(145, -1);
	optimal[1] = 0;
	for (int i = 2; i <= 144; ++i) {
		int op = 1000, opid = -1;
		for (int j = 1; j < i; ++j) {
			if (max(2 + optimal[j], 1 + optimal[i - j]) < op) {
				op = max(2 + optimal[j], 1 + optimal[i - j]);
				opid = j;
			}
		}
		cout << "Optimal for " << i << ": " << opid << " for a cost of " << op << endl;
		optimal[i] = op;
		optleft[i] = opid;
	}
	
	if (n < optimal[144]) {
		cout << "Not enough money" << endl;
	} else {
		cout << "Let's play!" << endl;
		int l = 1, r = 144;
		while (l < r) {
			int m = l - 1 + optleft[r - l + 1];
			cout << (m - l + 1);
			for (int i = l; i <= m; ++i) cout << ' ' << i;
			cout << endl;
			string ans;
			cin >> ans;
			if (ans == "Yes")
				r = m;
			else
				l = m + 1;
		}
		cout << 0 << ' '  << l << endl;
	}
	
	
	return 0;
}
