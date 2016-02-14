#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

template <class T>
T dot(T x1, T y1, T z1, T x2, T y2, T z2) {
	return x1*x2 + y1*y2 + z1*z2;
}
ll lsq(ll x, ll y, ll z) {
	return dot<ll>(x, y, z, x, y, z);
}

vector<vector<ll> > rec(4, vector<ll>(3, 0LL));
bool valid(vector<vector<ll> > &X, int i, int j, int k,
	vector<ll> &mn, vector<ll> &mx, vector<ll> &sm) {
	// The basis vectors are i-0, j-0, k-0
	
	// should be independent
	if (dot<ll>(X[i][0]-X[0][0], X[i][1]-X[0][1], X[i][2]-X[0][2],
		X[j][0]-X[0][0], X[j][1]-X[0][1], X[j][2]-X[0][2]) != 0)
		return false;
	if (dot<ll>(X[i][0]-X[0][0], X[i][1]-X[0][1], X[i][2]-X[0][2],
		X[k][0]-X[0][0], X[k][1]-X[0][1], X[k][2]-X[0][2]) != 0)
		return false;
	if (dot<ll>(X[k][0]-X[0][0], X[k][1]-X[0][1], X[k][2]-X[0][2],
		X[j][0]-X[0][0], X[j][1]-X[0][1], X[j][2]-X[0][2]) != 0)
		return false;
	// should have the same nonzero length
	ll l1 = lsq(X[i][0]-X[0][0], X[i][1]-X[0][1], X[i][2]-X[0][2]);
	ll l2 = lsq(X[j][0]-X[0][0], X[j][1]-X[0][1], X[j][2]-X[0][2]);
	ll l3 = lsq(X[k][0]-X[0][0], X[k][1]-X[0][1], X[k][2]-X[0][2]);

	if (l1 != l2) return false;
	if (l1 != l3) return false;
	if (l1 ==  0) return false;
	
//	cerr << "Passed dotproduct" << endl;
//	cerr << i << ' ' << j << ' ' << k << ' ' << endl;
	
	// remaining vertices
	for (int n = 0; n < 3; ++n) {
		rec[0][n] = X[i][n] + X[j][n] - X[0][n];
		rec[1][n] = X[j][n] + X[k][n] - X[0][n];
		rec[2][n] = X[i][n] + X[k][n] - X[0][n];
		rec[3][n] = X[i][n] + X[j][n] + X[k][n] - 2 * X[0][n];
	}
	
	vb available(4, true);
	for (int n = 1; n < 8; ++n) {
		if (n == i || n == j || n == k) continue;
		
		// Can we permute X[n] to get rec[m]
		for (int m = 0; m < 4; ++m) {
			if (!available[m]) continue;
			if (mn[n] != min(rec[m][0],
					min(rec[m][1], rec[m][2])))
				continue;
			if (mx[n] != max(rec[m][0],
					max(rec[m][1], rec[m][2])))
				continue;
			if (sm[n] != rec[m][0] + rec[m][1] + rec[m][2])
				continue;
			
			X[n][0] = rec[m][0];
			X[n][1] = rec[m][1];
			X[n][2] = rec[m][2];
			
			// Permute coordinates accordingly
			available[m] = false;
			break;
		}
	}
	
	available[0] = available[0] || available[1];
	available[2] = available[2] || available[3];
	available[0] = available[0] || available[2];
	return !available[0];
}

void printrow(vector<ll> &v) {
	cout << v[0] << ' ' << v[1] << ' ' <<v[2] << endl;
}

void print(vector<vector<ll> > &X, int i, int j, int k) {
	cout << "YES" << endl;
	for (int i = 0; i < 8; ++i)
		printrow(X[i]);
}

int main() {
	
	vector<vector<ll> > X(8, vector<ll>(3, 0LL));
	vector<ll> mn(8, LLINF), mx(8, -LLINF), sm(8, 0LL);
	for (int i = 0; i < 8; ++i) {
		cin >> X[i][0] >> X[i][1] >> X[i][2];
		sort(X[i].begin(), X[i].end());
		mn[i] = X[i][0];
		mx[i] = X[i][2];
		sm[i] = X[i][0] + X[i][1] + X[i][2];
	}
	
	// For all 3-subsets of 1..7
	for (int i = 1; i < 8; ++i) {
		sort(X[i].begin(), X[i].end());
		do {
			for (int j = i + 1; j < 8; ++j) {
				sort(X[j].begin(), X[j].end());
				do {
					for (int k = j + 1; k < 8; ++k) {
						sort(X[k].begin(), X[k].end());
						do {
							if (valid(X, i, j, k, mn, mx, sm)) {
								print(X, i, j, k);
								return 0;
							}
						} while (next_permutation(X[k].begin(), X[k].end()));
					}
				} while (next_permutation(X[j].begin(), X[j].end()));
			}
		} while (next_permutation(X[i].begin(), X[i].end()));
	}
	
	cout << "NO" << endl;
	
	return 0;
}
