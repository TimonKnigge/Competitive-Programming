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
using ull = unsigned long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

void mk(pair<ld, pair<ld, ll> > v){ 
	cerr << "{" << v.first << ",{" << v.second.first << "," << v.second.second << "}}";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	ld p[4][21];
	cin >> p[0][1] >> p[1][1] >> p[2][1] >> p[3][1];
	for (int c = 0; c < 4; ++c) {
		p[c][0] = 1.0;
		for (int i = 2; i <= 20; ++i)
			p[c][i] = p[c][1] * p[c][i - 1];
	}
	
	vector<ull> fac(21, 1LL);
	for (ull i = 1; i <= 20; ++i)
		fac[int(i)] = fac[int(i - 1ULL)] * i;
	
	priority_queue<
		pair<ld, pair<ld, ll> >,
		vector<pair<ld, pair<ld, ll> > >,
		greater<pair<ld, pair<ld, ll> > >
		> pq;
	for (int i1 = 0; i1                <= n; ++i1)
	for (int i2 = 0; i1 + i2           <= n; ++i2)
	for (int i3 = 0; i1 + i2 + i3      <= n; ++i3) {
		int i4 = n - i1 - i2 - i3;
		ull cnt = fac[n];
		cnt /= fac[i1];
		cnt /= fac[i2];
		cnt /= fac[i3];
		cnt /= fac[i4];
		ld prob = p[0][i1] * p[1][i2] * p[2][i3] * p[3][i4];
		if (prob > 0.0)
			pq.push({prob, {0.0, cnt}});
	}
	
	while (pq.size() > 1 || pq.top().second.second > 1LL) {
		auto top = pq.top();
//		cerr << "Taking "; mk(top); cerr << endl;
		pq.pop();
		if (top.second.second > 1LL) {
			if (top.second.second&1) {
				auto nxt = top;
				nxt.second.second = 1LL;
//				cerr << "Pushing "; mk(nxt); cerr << endl;
				pq.push(nxt);
				--top.second.second;
			}
			top.first *= 2.0;
			top.second.first = (1.0 + top.second.first);
			top.second.second /= 2LL;
//			cerr << "Pushing "; mk(top); cerr << endl;
			pq.push(top);
		} else {
			auto top2 = pq.top();
//			cerr << "Taking "; mk(top2); cerr << endl;
			pq.pop();
			if (top2.second.second > 1LL) {
				top2.second.second--;
				pq.push(top2);
//				cerr << "Pushing "; mk(top2); cerr << endl;
			}
			top = {top.first + top2.first,
				{top.first * (1.0 + top.second.first)  / (top.first + top2.first)
				+top2.first* (1.0 + top2.second.first) / (top.first + top2.first),
				1LL}};
//			cerr << "Pushing "; mk(top); cerr << endl;
			pq.push(top);
		}
	}
	
	printf("%.7lf\n", double(pq.top().second.first));
//	printf("%.7lf\n", double(pq.top().first));
	
	return 0;
}
