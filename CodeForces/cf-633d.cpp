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

void add(map<ll, int> &m, ll v) {
	auto it = m.find(v);
	if (it == m.end()) m.insert({v, 1});
	else it->second++;
}
void remove(map<ll, int> &m, ll v) {
	auto it = m.find(v);
	if (it->second > 1) it->second--;
	else m.erase(it);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	vi A(N, 0LL);
	for (int i = 0; i < N; ++i)
		cin >> A[i];
	
	sort(A.begin(), A.end());
	
	set<ii> had;
	map<ll, int> rem;
	for (ll v : A) add(rem, v);
	vi q;
	ll L = 2LL;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			if (i == j) continue;
			if (had.find({A[i], A[j]}) != had.end()) continue;
			q.push_back(A[i]);
			q.push_back(A[j]);
			remove(rem, A[i]);
			remove(rem, A[j]);
			had.insert({A[i], A[j]});
			
			while (rem.size() > 0) {
				ll nxt = q.back() + q[q.size()-2];
				if (rem.find(nxt) == rem.end()) break;
				remove(rem, nxt);
				q.push_back(nxt);
			}
			if (q.size() > L) {
				L = q.size();
			}
			while (q.size() > 0) {
				add(rem, q.back());
				q.pop_back();
			}
		}
	
	cout << L << endl;
	
	return 0;
}
