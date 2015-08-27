#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <cstdio>

using namespace std;

void readn(register int *n) {
	cin >> (*n);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int k, n;
	readn(&k);
	readn(&n);
	
	vector<vector<int> > e(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		int sz;
		readn(&sz);
		for (int j = 0; j < sz; ++j) {
			int v;
			readn(&v);
			v--;
			e[i].push_back(v);
		}
	}
	
	auto beg = chrono::high_resolution_clock::now();
	bool pos = false;
	vector<bool> vb(n, false);
	vector<int> ch;
	int N = n;
	while (true) {
		auto en = chrono::high_resolution_clock::now();
		if (chrono::duration_cast<chrono::milliseconds>(en-beg).count() > 1750)
			break;
		N = n;
		
		// Find a random assignment
		bool unexp = false;
		for (int i = 0; i < k; ++i) {
			if (N <= 0) { unexp = true; break; }

			int j = rand() % n;
			while (vb[j]) j = rand() % n;
			vb[j] = true;
			ch.push_back(j);
			N--;
			for (int a : e[j]) { if (!vb[a]) { vb[a] = true; N--; } }
		}

		if (!unexp) { pos = true; break; }
		
		for (int j : ch) {
			vb[j] = false;
			for (int i : e[j])
				vb[i] = false;
		}
		ch.clear();
	}
	
	cout << (pos ? "possible" : "impossible") << endl;
	
	return 0;
}

