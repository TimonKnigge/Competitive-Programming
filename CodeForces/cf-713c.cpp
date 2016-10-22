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
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vi a(n, 0LL);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	
	vi b(a);
	ll cost = 0LL;
	for (int i = 1; i < n; ++i) {
		if (b[i - 1] >= b[i]) {
			cost += b[i - 1] - b[i] + 1;
			b[i] = 1 + b[i - 1];
		}
	}
	
//	cerr << "Initial cost at " << cost << endl;
//	for (int i = 0; i < n; ++i) cerr << ' ' << b[i];
//	cerr << endl;
	
	vii gains;
	vi carry;
	gains.reserve(n);
	carry.reserve(n);
	
	gains.push_back({1, LLINF}); // (cost, amount)
	carry.push_back(0);
	for (int i = 1; i < n; ++i) {
		if (b[i] > 1 + b[i - 1]) {
			gains.push_back({0, b[i] - b[i - 1] - 1});
			carry.push_back(0);
		}
		
		ll neg = b[i] - a[i];
		for (int j = int(gains.size()) - 1; j >= 0; --j) {
			if (neg > 0) {
				if (neg >= gains[j].second) {
					neg -= gains[j].second;
					gains[j].first--;
				} else {
					gains[j].second -= neg;
					gains[j].first++;
					gains.insert(gains.begin() + j + 1, ii(gains[j].first-2, neg));
					carry.insert(carry.begin() + j, 0);
					neg = 0;
				}
			} else {
				carry[j]++;
				break;
//				gains[j].first++;
			}
		}
		
//		cerr << "Gains now at:";
//		for (auto v : gains) cerr << " (" << v.first << "," << v.second << ")";
//		cerr << endl;
		
		while (gains.size() > 0 && gains.back().first + carry.back() < 0) {
			gains.back().first += carry.back();
			cost += gains.back().first * gains.back().second;
			b[i] -= gains.back().second;
//			for (int j = i - 1; j >= 0; --j) {
//				if (b[j] >= b[j + 1]) b[j] = b[j + 1] - 1;
//			}
			gains.pop_back();
			ll c = carry.back();
			carry.pop_back();
			if (carry.size() > 0) carry.back() += c;
		}
	}
	
	cout << cost << endl;
	
	return 0;
}
