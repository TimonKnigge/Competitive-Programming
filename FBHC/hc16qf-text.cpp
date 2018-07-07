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
const ll LLINF = 9000000000000000000LL;

struct Node {
	ll optimal[301];
	int ch[26], depth = 0;
	bool word = false;
	Node() {
		for (int i = 0; i < 26; ++i) ch[i] = -1;
	}
};
constexpr int TS = 100100;
vector<Node> tree(TS, Node());
int F = 1;

void insert(string &s) {
	int ix = 0;
	for (int i = 0; i < int(s.length()); ++i) {
		int v = s[i] - 'a';
		if (tree[ix].ch[v] != -1) {
			ix = tree[ix].ch[v];
		} else {
			tree[ix].ch[v] = F;
			tree[F].depth = tree[ix].depth + 1;
			ix = F;
			F++;
		}
	}
	tree[ix].word = true;
}

ll calc_optimal(int bound) {
	for (int j = F - 1; j >= 0; --j) {
		for (int i = 0; i <= bound; ++i) {
			tree[j].optimal[i] = LLINF;
		}
		tree[j].optimal[0] = 0;
		if (tree[j].word)
			tree[j].optimal[1] = 1;
		int last = 1;
		for (int c = 0; c < 26; ++c) {
			if (tree[j].ch[c] == -1) continue;
			int cc = tree[j].ch[c];
			for (int d = last; d >= 0; --d) {
				if (tree[j].optimal[d] == LLINF) continue;
				for (int v = 0; d + v <= bound; ++v) {
					if (tree[cc].optimal[v] == LLINF) continue;
					tree[j].optimal[d + v] = min(tree[j].optimal[d + v], tree[j].optimal[d] + tree[cc].optimal[v] + 2);
					if (d + v > last) last = d + v;
				}
			}
		}
	}
	return tree[0].optimal[bound];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	cin >> T;
	for (int t = 1; t <= T; ++t) {
		
		tree.assign(TS, Node());
		F = 1;
		
		int N, K;
		cin >> N >> K;
		vector<string> W(N, "");
		for (int i = 0; i < N; ++i) {
			cin >> W[i];
			insert(W[i]);
		}
		
//		for (int i = 0; i < F; ++i) {
//			cerr << i << " (" << tree[i].word << ") ";
//			for (int j = 0; j < 26; ++j)
//				if (tree[i].ch[j] != -1) cerr << tree[i].ch[j] << " ";
//			cerr << endl;
//		}
		
		cout << "Case #" << t << ": " << calc_optimal(K) << '\n';
		cout << flush;
	}
	cout << flush;
	
	return 0;
}
