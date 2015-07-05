#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <stdio.h>

using namespace std;

template<class T>
struct DPTable {
	T* table[2];
	int n, m;
	DPTable(int _n, int _m) : n(_n), m(_m) {
		table[0] = new T[_m];
		table[1] = new T[_m];
	}
	T g(int i, int j) { return table[i % 2][j]; }
	void s(int i, int j, T v) { table[i % 2][j] = v; }
	void cleanup() { delete[] table[0]; delete[] table[1]; }
};

int main() {

	int n, t; 
	long double p;
	cin >> n >> p >> t;

	DPTable<long double> dp(t + 1, n + 1);
	dp.s(0, 0, 1.0);
	for (int i = 1; i <= n; ++i) 
		dp.s(0, i, 0.0);

	for (int j = 1; j <= t; ++j) {
		dp.s(j, 0, (1 - p) * dp.g(j - 1, 0));
		for (int i = 1; i < n; ++i)
			dp.s(j, i, (1 - p) * dp.g(j - 1, i) + p * dp.g(j - 1, i - 1));
		dp.s(j, n, dp.g(j - 1, n) + p * dp.g(j - 1, n - 1));
	}

	long double expected = 0.0;
	for (int i = 1; i <= n; ++i) {
		expected += dp.g(t, i) * i;
	}

	printf("%.7f\n", (double)expected);
	return 0;
}