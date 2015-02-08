#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef long long ll;

bool setContainsItem(int set, int item) {
	return ((set & (1 << item)) == (1 << item));
}
bool setContainsSet(int setSmall, int setLarge) {
	return ((setSmall & setLarge) == setSmall);
}

int main(){

	int n;
	cin >> n;

	// Read input
	vvi options(n);
	for (int p = 0; p < n; ++p) {
		int m;
		cin >> m;
		for (int i = 0; i < m; ++i) {
			string word;
			cin >> word;
			int val = 0;
			for (int j = 0; j < word.length(); ++j) {
				val |= (1 << (word.at(j) - 'a'));
			}
			options[p].push_back(val);
		}
	}

	vvi pToq(n, vi(n, -1));
	for (int p = 0; p < n; ++p) {
		int S = 1 << p;
		pToq[p][p] = 0;
		for (int it = 1; it <= n; ++it) {
			int newS = S;
			for (int q = 0; q < n; ++q) {
				if (pToq[p][q] != -1) continue;
				for (int subs : options[q]) {
					if (setContainsSet(subs, S)) {
						pToq[p][q] = it;
						newS |= (1 << q);
						break;
					}
				}
			}
			S = newS;
		}
	}

	for (int p = 0; p < n; ++p) {
		for (int q = 0; q < n; ++q) {
			cout << pToq[q][p] << ' ';
		}
		cout << endl;
	}

	return 0;
}