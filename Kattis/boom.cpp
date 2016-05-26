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

constexpr int DIM = 1005;
int network[DIM][DIM];
int fleft[DIM][DIM], fup[DIM][DIM], fright[DIM][DIM], fdown[DIM][DIM];

void try_enqueue(queue<ii> &q, vector<string> &board, int r, int c, int nr, int nc, int R) {
	if (board[nr][nc] != '*' || network[nr][nc] >= 0) return;
	if (abs(r - nr) + abs(c - nc) > R) return;
	network[nr][nc] = network[r][c];
	q.push({nr, nc});
}

template<class T>
void inc(map<T, ll> &m, T t) {
	auto it = m.find(t);
	if (it == m.end()) m.insert({t, 1LL});
	else it->second++;
}

template<class T>
ll calc(map<T, ll> &m, T t) {
	auto it = m.find(t);
	if (it == m.end()) return 0LL;
	else return it->second;
}

int fmore(vi &A, int w) {
	int l = 0, r = A.size();
	while (l < r) {
		int m = (l+r) / 2;
		if (A[m] < w)
			l = m + 1;
		else	r = m;
	}
	return l;
}

ll inrange(vi &A, int L, int R) {
	return fmore(A, R+1) - fmore(A, L);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, R;
	cin >> N >> R >> ws;
	
	vector<string> board(N, "");
	for (int r = 0; r < N; ++r) {
		getline(cin, board[r]);
		for (int c = 0; c < N; ++c) {
			network[r][c] = -1;
			fleft[r][c] = fup[r][c] = -1;
			fright[r][c] = fdown[r][c] = N;
		}
	}
	
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			if (board[r][c] == '*' || board[r][c] == '#')
				fleft[r][c] = c;
			else	fleft[r][c] = (c > 0 ? fleft[r][c-1] : -1);
		}
		for (int c = N - 1; c >= 0; --c) {
			if (board[r][c] == '*' || board[r][c] == '#')
				fright[r][c] = c;
			else	fright[r][c] = (c+1<N ? fright[r][c+1] : N);
		}
	}
	for (int c = 0; c < N; ++c) {
		for (int r = 0; r < N; ++r) {
			if (board[r][c] == '*' || board[r][c] == '#')
				fup[r][c] = r;
			else	fup[r][c] = (r > 0 ? fup[r-1][c] : -1);
		}
		for (int r = N - 1; r >= 0; --r) {
			if (board[r][c] == '*' || board[r][c] == '#')
				fdown[r][c] = r;
			else	fdown[r][c] = (r+1<N ? fdown[r+1][c] : N);
		}
	}
	
	int NW = 0;
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c) {
			if (board[r][c] != '*' || network[r][c] >= 0) continue;
			network[r][c] = NW;
			
			queue<ii> q;
			q.push({r, c});
			while (!q.empty()) {
				int rr = q.front().first;
				int cc = q.front().second;
				q.pop();

				if (cc > 0 && fleft[rr][cc-1] >= 0)
					try_enqueue(q, board, rr, cc, rr, fleft[rr][cc-1], R);
				if (cc + 1 < N && fright[rr][cc+1] < N)
					try_enqueue(q, board, rr, cc, rr, fright[rr][cc+1], R);
				if (rr > 0 && fup[rr-1][cc] >= 0)
					try_enqueue(q, board, rr, cc, fup[rr-1][cc], cc, R);
				if (rr + 1 < N && fdown[rr+1][cc] < N)
					try_enqueue(q, board, rr, cc, fdown[rr+1][cc], cc, R);
			}
			
			NW++;
		}
	
	int stumps = 0;
	map<ll, ll> f1;
	map<ii, ll> f2;
	map<pair<ll, ii>, ll> f3;
	map<pair<ii, ii>, ll> f4;
	
//	vvi freer(N, vi()), freec(N, vi());
	vector<vector<set<ll>>> st(N, vector<set<ll>>(N, set<ll>()));
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c) {
			if (board[r][c] != 'S') continue;
			++stumps;
			
			if (fleft[r][c] >= 0 && c-fleft[r][c] <= R && board[r][fleft[r][c]] == '*')
				st[r][c].insert(network[r][fleft[r][c]]);
			if (fright[r][c] < N && fright[r][c]-c <= R && board[r][fright[r][c]] == '*')
				st[r][c].insert(network[r][fright[r][c]]);
			if (fup[r][c] >= 0 && r-fup[r][c] <= R && board[fup[r][c]][c] == '*')
				st[r][c].insert(network[fup[r][c]][c]);
			if (fdown[r][c] < N && fdown[r][c]-r <= R && board[fdown[r][c]][c] == '*')
				st[r][c].insert(network[fdown[r][c]][c]);
			
			if (st[r][c].size() > 0) {
				vi items;
				copy(st[r][c].begin(), st[r][c].end(), back_inserter(items));
				for (size_t i1 = 0; i1 < items.size(); ++i1) {
					inc(f1, items[i1]);
					for (size_t i2 = i1 + 1; i2 < items.size(); ++i2) {
						inc(f2, {items[i1], items[i2]});
						for (size_t i3 = i2 + 1; i3 < items.size(); ++i3) {
							inc(f3, {items[i1], {items[i2], items[i3]}});
							for (size_t i4 = i3 + 1; i4 < items.size(); ++i4)
								inc(f4, {{items[i1], items[i2]}, {items[i3], items[i4]}});
						}
					}
				}
			} 
//			else {
//				freer[r].push_back(c);
//				freec[c].push_back(r);
//			}
		}
	
	ll ans = 0LL;
	for (int r = 0; r < N; ++r)
		for (int c = 0; c < N; ++c) {
			if (board[r][c] != '.') continue;
			
			int covered = 0;
			// free
//			covered += inrange(freer[r], max(fleft[r][c]+1, c-R), min(fright[r][c]-1, c+R));
//			covered += inrange(freec[c], max(fup[r][c]+1, r-R), min(fdown[r][c]-1, r+R));
			
			// by chain
			set<ll> cst;
			if (fleft[r][c] >= 0 && c-fleft[r][c] <= R && board[r][fleft[r][c]] == '*')
				cst.insert(network[r][fleft[r][c]]);
			if (fright[r][c] < N && fright[r][c]-c <= R && board[r][fright[r][c]] == '*')
				cst.insert(network[r][fright[r][c]]);
			if (fup[r][c] >= 0 && r-fup[r][c] <= R && board[fup[r][c]][c] == '*')
				cst.insert(network[fup[r][c]][c]);
			if (fdown[r][c] < N && fdown[r][c]-r <= R && board[fdown[r][c]][c] == '*')
				cst.insert(network[fdown[r][c]][c]);
			
			if (cst.size() > 0) {
				vi items;
				copy(cst.begin(), cst.end(), back_inserter(items));
				for (size_t i1 = 0; i1 < items.size(); ++i1) {
					covered += calc(f1, items[i1]);
					for (size_t i2 = i1 + 1; i2 < items.size(); ++i2) {
						covered -= calc(f2, {items[i1], items[i2]});
						for (size_t i3 = i2 + 1; i3 < items.size(); ++i3) {
							covered += calc(f3, {items[i1], {items[i2], items[i3]}});
							for (size_t i4 = i3 + 1; i4 < items.size(); ++i4)
								covered -= calc(f4, {{items[i1], items[i2]}, {items[i3], items[i4]}});
						}
					}
				}
			}
			
			// free
			for (int i = max(fleft[r][c]+1, c-R); i <= min(fright[r][c]-1, c+R); ++i)
				if (board[r][i] == 'S') {
					bool cov = false;
					for (ll nw : st[r][i]) if (cst.find(nw) != cst.end()) cov = true;
					if (!cov) ++covered;
				}
			for (int i = max(fup[r][c]+1, r-R); i <= min(fdown[r][c]-1, r+R); ++i)
				if (board[i][c] == 'S') {
					bool cov = false;
					for (ll nw : st[i][c]) if (cst.find(nw) != cst.end()) cov = true;
					if (!cov) ++covered;
				}
			if (covered == stumps) ++ans;
		}
	
	cout << ans << endl;
	
	return 0;
}
