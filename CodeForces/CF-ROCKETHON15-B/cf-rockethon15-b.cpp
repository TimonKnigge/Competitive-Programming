#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

bool bitIsSet(ll val, int pos) {
	return ((val & (1LL << pos)) == (1LL << pos));
}

int main() {

	// Read input
	int n; ll m;
	cin >> n >> m;
	vi permutation(n);

	// Fill in the permutation from both sides,
	// using m as a bitmask to determine from which
	// side to push in each value.
	int l = 0, r = n - 1;
	m--;
	for (int v = 1; v < n; ++v) {
		if (!bitIsSet(m, n - v - 1)) {
			permutation[l] = v;
			l++;
		}
		else {
			permutation[r] = v;
			r--;
		}
	}
	// One spot left for the last number.
	permutation[l] = n;

	// Do output
	cout << permutation[0];
	for (int i = 1; i < n; ++i)
		cout << ' ' << permutation[i];
	cout << endl;

	return 0;
}