#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;	                 // 9
const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

#ifdef _MSC_VER
#define popcount(x) __popcnt(x)
#else
#define popcount(x) __builtin_popcount(x)
#endif

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// I\O
	int n, m;
	cin >> n >> m;
	vi p(n, -1), symbol(n, 0);
	vvi child(n, vi());
	for (int i = 1; i < n; ++i) { 
		cin >> p[i]; 
		p[i]--;
		child[p[i]].push_back(i);
	}
	string str; cin >> str;
	for (int i = 0; i < n; ++i) {
		symbol[i] = (1 << (str[i] - 'a'));
	}
	
	// DFS preordering, calculate depth, etc
	vi dfsno(n, -1), dfsub(n, -1), depth(n, 0), atd_ind(n, -1);
	vvi atdepth(n, vi());
	int c = 0;
	vb vis(n, false);
	stack<int> st; st.push(0);
	while (!st.empty()) {
		int u = st.top();
		if (vis[u]) {
			dfsub[u] = c; c++;
			st.pop();
		} else {
			vis[u] = true;
			dfsno[u] = c; c++;
			atd_ind[u] = atdepth[depth[u]].size();
			atdepth[depth[u]].push_back(u);
			for (int v : child[u]) {
				depth[v] = depth[u] + 1;
				st.push(v);
			}
		}
	}

//	for (int i = 0; i < n; ++i) {
//		cout << i <<": ";
//		for (int j : atdepth[i]) cout << j << '('<<dfsno[j]<<')'<< ' ';cout<<endl;
//	}

	// Find prefix-xors for each depth, as well as intervals
	vvi pfxor(n, vi());
	for (int d = 0; d < n; ++d) {
		if (atdepth[d].size() == 0) continue;
		pfxor[d].assign(atdepth[d].size(), 0);
		pfxor[d][0] = symbol[atdepth[d][0]];
		for (int j = 1; j < atdepth[d].size(); ++j) {
			pfxor[d][j] = (pfxor[d][j - 1] ^ symbol[atdepth[d][j]]);
		}
	}
	
	// Take queries
	for (int q = 0; q < m; ++q) {
		int v, h;
		cin >> v >> h;
		v--; h--;
		int lb = dfsno[v];
		int ub = dfsub[v];
		// At depth h, find interval [lb, ub)
		bool isp = true;
		if (atdepth[h].size() == 0) isp = true;
		else if (h < depth[v]) isp = true;
		else {
			int l = 0, r = atdepth[h].size() - 1;
			while (l < r) {
				int m = (l + r) / 2;
				if (dfsno[atdepth[h][m]] >= lb) r = m;
				else l = m + 1;
			}
			int ilb = l;
			l = 0; r = atdepth[h].size() - 1;
			while (l < r) {
				int m = (l + r) / 2;
				if (dfsno[atdepth[h][m]] >= ub) r = m;
				else l = m + 1;
			}
			int iub = l;
			ilb--;
			if (dfsno[atdepth[h][iub]] >= ub) iub--;
//			cerr << '(' << ilb << ',' << iub << ']';
//			cerr << " based on " << lb << " - " << ub << endl;
			int ans = (iub >= 0 ? pfxor[h][iub] : 0) ^ (ilb >= 0 ? pfxor[h][ilb] : 0);
			isp = (popcount(ans) <= 1);
		}
		cout << (isp ? "Yes\n" : "No\n");
	}
	cout << flush;
	
	return 0;
}
