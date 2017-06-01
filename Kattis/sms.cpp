#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

constexpr int INF = 2000000000;
constexpr ll LLINF = 9000000000000000000;

// TRIE
constexpr int ALPHABET_SIZE = 26;
inline int mp(char c) { return c - 'a'; }

struct Node {
	Node* ch[ALPHABET_SIZE];
	int id = -1;
	Node() { for(int i = 0; i < ALPHABET_SIZE; ++i) ch[i] = nullptr; }
	void insert(const string &s, int index, size_t i = 0) {
		if (i == s.length()) {
			id = index;
		} else {
			int v = mp(s[i]);
			if (ch[v] == nullptr)
				ch[v] = new Node();
			ch[v]->insert(s, index, i + 1);
		}
	}
	void update(const string &s, size_t i, vi &dp, vi &p, const vi &cost,
			const vector<string> &words, ll sc) {
		if (id != -1) {
			ll c = sc + abs(cost[id]) + 1LL
				+ ll(words[id].length());
			if (c < dp[i] || p[i] < 0LL) {
				dp[i] = c;
				p[i] = id;
			}
		}
		if (i < s.length()) {
			int v = mp(s[i]);
			if (ch[v] != nullptr)
				ch[v]->update(s, i+1, dp, p, cost, words, sc);
		}
	}
};
//-TRIE

constexpr int dtable[26] = {
	0, 0, 0,
	1, 1, 1,
	2, 2, 2,
	3, 3, 3,
	4, 4, 4,
	5, 5, 5, 5,
	6, 6, 6,
	7, 7, 7, 7 };
ll shash(const string &s) {
	ll r = 0LL, c = 1LL;
	for (size_t i = 0; i < s.length(); ++i, c *= 9LL)
		r += c * ll(1+dtable[s[i] - 'a']);
	return r;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N; cin >> N;
	vector<string> words(N, "");
	vi cost(N, 0LL);
	Node *root = new Node();
	{
		unordered_map<ll, int> count;
		for (int i = 0; i < N; ++i) {
			cin >> words[i];
			cost[i] = count[shash(words[i])]++;
			root->insert(words[i], i);
		}
		for (int i = 0; i < N; ++i) {
			ll c = count[shash(words[i])];
			if (c - cost[i] < cost[i]) cost[i] -= c;
//			cerr << "Word " << words[i] << " has cost " << cost[i]
//				<< endl;
		}
	}
	
	int Q; cin >> Q;
	while (Q--) {
		string S; cin >> S;
		vi dp(S.length()+1, -1LL), p(S.length()+1, -1LL);
		dp[0] = 0LL;
		for (size_t i = 0; i < S.length(); ++i)
//			cerr << "Beginning update from " << i << endl,
			root->update(S, i, dp, p, cost, words, dp[i]);
//		cerr << "Requires " << dp.back() << " keypresses." << endl;
		
		vi sol; int cur = (int)S.length();
		while (cur > 0)
			sol.push_back(p[cur]),
			cur -= (int)words[p[cur]].length();
		for (int i = (int)sol.size()-1; i >= 0; --i) {
			for (size_t j = 0; j < words[sol[i]].length(); ++j)
				cout << 2+dtable[words[sol[i]][j]-'a'];
			if (cost[sol[i]] > 0LL)
				cout << "U(" <<  cost[sol[i]] << ")";
			else if (cost[sol[i]] < 0LL)
				cout << "D(" << -cost[sol[i]] << ")";
			if (i > 0)
				cout << "R";
			else	cout << '\n';
		}
	}
	cout << flush;
	
	return 0;
}
