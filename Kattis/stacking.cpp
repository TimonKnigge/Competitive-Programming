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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, tcase = 1;
	while (cin >> N) {
		
		set<int> found;
		vvi st(N, vi());
		for (int i = 0; i < N; ++i) {
			int h;
			cin >> h;
			while (h--) {
				int v;
				cin >> v;
				if (st[i].size() == 0 || st[i].back() != v)
					st[i].push_back(v);
				if (found.find(v) == found.end())
					found.insert(v);
			}
		}
		
		int M = found.size();
		map<int, int> mp;
		int id = 0;
		for (auto it = found.begin(); it != found.end(); ++it) {
			mp[*it] = id;
			++id;
		}
		
		vi c(M, 0);
		for (int i = 0; i < N; ++i) {
			int h = int(st[i].size());
			for (int j = 0; j < h; ++j) {
				st[i][j] = mp[st[i][j]];
				c[st[i][j]]++;
			}
			reverse(st[i].begin(), st[i].end());
		}
		
		vvi dp(M, vi(N, INF));
		for (int i = 0; i < N; ++i) {
			if (st[i].back() != 0) continue;
			int cost = 0; // (st[i].size() >  ? 1 : 0);
			for (int j = 0; j < N; ++j) {
				if (j == i) continue;
				if (st[j].back() != 0) continue;
				if (st[j].size() > 1) cost++;
				cost++;
			}
//			cout << st[i].size() << ' ' << st.back() <<endl;
			dp[0][i] = cost;
		}
		for (int i = 0; i < N; ++i)
			if (st[i].back() == 0) st[i].pop_back();
		
		for (int c = 1; c < M; ++c) {
			for (int i = 0; i < N; ++i) {
				if (st[i].back() != c) continue;
				for (int j = 0; j < N; ++j) {
					int cost = dp[c - 1][j];
					
					bool anyibt = false;
					for (int k = 0; k < N; ++k) {
//					cerr << "st[" << k << "]: ";
//					for (int j =0;j<st[k].size();++j)
//					cerr << st[k][j]<<' ';cerr<<endl;
						if (i == k || j == k) continue;
						if (st[k].size() == 0) continue;
						if (st[k].back() != c) continue;
						if (st[k].size() > 1) cost++;
						cost++;
						anyibt = true;
					}
					if (i != j) cost++;
					if (i != j && (
						(st[j].size() > 1 && st[j].back() == c) 
						|| (st[j].size()>0 && st[j].back() != c)))
						cost++;
					if (anyibt && i == j) cost += 2;
					dp[c][i] = min(dp[c][i], cost);
//					cerr << c << "," << i <<"," << j<<","<<cost<<endl;
				}
//					cerr << "dp["<<c<<"]["<<i<<"] = " << dp[c][i]<<endl;
			}
			
			for (int i = 0; i < N; ++i)
				if (st[i].size() > 0 && st[i].back() == c)						st[i].pop_back();
		}
		
		int opt = INF;
		for (int i = 0; i < N; ++i)
			opt = min(opt, dp[M - 1][i]);
		
		cout << "Case " << tcase << ": " << opt << endl;
		++tcase;
	}
	
	return 0;
}
