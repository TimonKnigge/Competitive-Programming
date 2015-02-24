#include <iostream>
#include <vector>
#include <math.h>
#include <bitset>

using namespace std;

bitset<500> bs[500];

int main() {

	int n, m; long mod;
	cin >> n >> m >> mod;

	vector<int> col(n, 2), row(n, 2);

	for (int v = 0; v < m; ++v) {
		row[v] = 0;
		for (int h = 0; h < n; ++h) {
			char val;
			cin >> val;
			if (val == '1') {
				bs[v].set(h, true);
				col[h]--;
			}
			else{
				bs[v].set(h, false);
			}
		}
	}

	// bs[row]. (col)

	return 0;
}