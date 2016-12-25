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

bool run() {
	ld X;
	int K;
	cin >> X >> K;
	vector<ld> F(K, 0.0);
	for (ld &v : F) cin >> v;
	sort(F.begin(), F.end());
	if (F.front() * X <= 1.0) return true;
	
	priority_queue<
		pair<ld, ld>,
		vector<pair<ld, ld>>,
		greater<pair<ld, ld>>> pq;

	vector<pair<ld, ld>> wins(1, {0.0, 1.0 / F.front()});
	while (wins.back().second <= X) {
		if (pq.empty())
			for (ld f : F)
				pq.push({wins.back().second / f,
					 wins.back().second / F.back() / f});
		pair<ld, ld> w = pq.top();
		pq.pop();
		
		if (w.first <= wins.back().second)
			wins.back().second = max(wins.back().second, w.second);
		else {
			for (ld f : F)
				pq.push({wins.back().second / f,
					min(w.first, wins.back().second
							/ F.back()) / f});
			if (pq.top() < w) {
				pq.push(w);
				w = pq.top();
				pq.pop();
			}
			wins.push_back(w);
		}
	}

	return any_of(wins.begin(), wins.end(), [X](pair<ld, ld> p) {
		return p.first < X && X <= p.second;
	});
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	while (N--) cout << (run() ? "Nils" : "Mikael") << endl;
	
	return 0;
}
