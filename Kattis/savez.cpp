#include<bits/stdc++.h>

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

constexpr int ALPHABET_SIZE = 26;
inline int mp(char c) { return c - 'A'; }

struct Node {
	Node* ch[ALPHABET_SIZE];
	int id = -1;
	void insert(string&, int, vi&, vi&, int i = 0);
};
Node tra[4000010];
int tri = 0;

void Node::insert(string &s, int iid, vi &lseen, vi &vec, int i) {
	if (id >= 0) {
		if (lseen[id] < iid)
			lseen[id] = iid;
		else	vec.push_back(id);
	}
	if ((size_t)i == s.length()) id = iid;
	else {
		int v = mp(s[i]);
		if (ch[v] == nullptr) ch[v] = &tra[tri++];
		ch[v]->insert(s, iid, lseen, vec, i + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;	
	vector<string> S(N, "");
	for (int i = 0; i < N; ++i) cin >> S[i];
	
	Node *pr = &tra[tri++], *sf = &tra[tri++];
	vvi E(S.size(), vi());
	ll best = 0LL;
	vi mx(S.size(), 1LL), lseen(S.size(), -1);
	for (int i = 0; i < (int)S.size(); ++i) {
		pr->insert(S[i], i, lseen, E[i]);
		reverse(S[i].begin(), S[i].end());
		sf->insert(S[i], i, lseen, E[i]);
		for (int j : E[i]) mx[i] = max(mx[i], 1 + mx[j]);
		best = max(mx[i], best);
	}
	
	cout << best << endl;
	
	return 0;
}
