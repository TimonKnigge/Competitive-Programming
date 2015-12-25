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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

struct state {
	unsigned long long v = 0ULL;
	state() { }
	void set(int i, int j, bool b) {
		if (b) v = v | (1ULL << (7 * i + j));
		else v = v &~ (1ULL << (7 * i + j));
	}
	bool get(int i, int j) {
		return bool(1&(v>>(7 * i + j)));
	}
	bool operator<(const state &rhs) const {
		return v < rhs.v;
	}
};

void printstate(state s) {
	cerr << "Board: " << endl;
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (s.get(i, j))
				cerr << 'X';
			else	cerr << '.';
		}
		cerr << endl;
	}
}

void precompute(map<state, int> &st, map<state, state> &par) {
	// initial states
	queue<pair<state, int> > q, pq;
	for (int j = 0; j < 7 - 2; ++j) {
		for (int i = 0; i < 7 - 2; ++i) {
			state s;
			for (int x = j; x < j + 3; ++x)
				for (int y = i; y < i + 3; ++y)
					s.set(x, y, true);
			q.push({s, 0});
			st.insert({s, 0});
		}
	}
	int cc = 0;
	while (!q.empty() || !pq.empty()) {
		cc++;
		queue<pair<state, int> > &rq = pq.empty() ? q : pq;
		state &s = rq.front().first;
		int dd = rq.front().second + 1;

		for (int r = 0; r < 7; ++r) {
			int i, j;
			for (i = 0; i < 7 && !s.get(r, i); ++i);
			if (i == 7) continue;
			for (j = i; j < 7 && s.get(r, j); ++j);
			// [i, j] is the leftmost segment
			int d = j - i;
			for (int t = 0; t < (d - 1); ++t) {
				state tmp = s;
				for (int k = 0; k <= t; ++k) {
					tmp.set(r, i + k, false);
				}
				for (int k = 0; k <= t; ++k) {
					tmp.set(r, k, true);
				}
				if (st.find(tmp) != st.end()) continue;
				st.insert({tmp, dd});
				q.push({tmp, dd});
//				par.insert({tmp, s});
			}
		}
		for (int r = 0; r < 7; ++r) {
			int i, j;
			for (i = 6; i >= 0 && !s.get(r, i); --i);
			if (i == -1) continue;
			for (j = i; j >= 0 && s.get(r, j); --j);
			// [j, i]
			int d = i - j;
			for (int t = 0; t < (d - 1); ++t) {
				state tmp = s;
				for (int k = 0; k <= t; ++k) {
					tmp.set(r, i - k, false);
				}
				for (int k = 0; k <= t; ++k) {
					tmp.set(r, 6 - k, true);
				}
				if (st.find(tmp) != st.end()) continue;
				st.insert({tmp, dd});
				q.push({tmp, dd});
//				par.insert({tmp, s});
			}
		}
		
		if (pq.empty()) {
			state s2 = s;
			for (int i = 0; i < 7; ++i)
				for (int j = i + 1; j < 7; ++j) {
					bool v1 = s.get(i, j), v2 = s.get(j, i);
					if (v1 != v2) {
						s2.set(i, j, v2);
						s2.set(j, i, v1);
					}
				}
			if (st.find(s2) == st.end()) {
				pq.push({s2, dd-1});
				st.insert({s2, dd-1});
//				par.insert({s2, s});
			}
		}
		
		rq.pop();
	}
}

int main() {
	
	map<state, int> st;
	map<state, state> par;
	precompute(st, par);
	cerr << st.size() << endl;

	int T;
	scanf("%d", &T);
	
	while (T--) {
		vector<string> in(7, "");
		for (int i = 0; i < 7; ++i)
			cin >> in[i];
		
		state s;
		for (int r = 0; r < 7; ++r) {
			for (int c = 0; c < 7; ++c)
				s.set(r, c, in[r][c] == 'X');
		}
		
		auto it = st.find(s);
		cout << (it != st.end() ? it->second : -1) << '\n';
//		if (it != st.end()) {
//			while (true) {
//				cerr << "Cost: " << st[s] << endl;
//				printstate(s);
//				auto it = par.find(s);
//				if (it == par.end()) break;
//				s = it->second;
//			}
//		}
	}
	
	return 0;
}
