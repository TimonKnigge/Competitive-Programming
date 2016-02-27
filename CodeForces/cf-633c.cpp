#include <iostream> 
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
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

int mfunc(char c) { return c - 'a'; }

template <int ALPHABET_SIZE, int (*mp)(char)>
struct AC_FSM {
	struct Node {
		int child[ALPHABET_SIZE], failure = 0, match_par = -1;
		vi match;
		Node() { for (int i = 0; i < ALPHABET_SIZE; ++i) child[i] = -1; }
	};
	vector <Node> a;
	AC_FSM() { a.push_back(Node()); }
	void construct_automaton(vector<string> &words) {
		for (int w = 0, n = 0; w < words.size(); ++w, n = 0) {
			for (int i = 0; i < words[w].size(); ++i) {
				if (a[n].child[mp(words[w][i])] == -1) {
					a[n].child[mp(words[w][i])] = a.size();
					a.push_back(Node());
				}
				n = a[n].child[mp(words[w][i])];
			}
			a[n].match.push_back(w);
		}

		queue<int> q;
		for (int k = 0; k < ALPHABET_SIZE; ++k) {
			if (a[0].child[k] == -1) a[0].child[k] = 0;
			else if (a[0].child[k] > 0) {
				a[a[0].child[k]].failure = 0;
				q.push(a[0].child[k]);
			}
		}
		while (!q.empty()) {
			int r = q.front(); q.pop();
			for (int k = 0, arck; k < ALPHABET_SIZE; ++k) {
				if ((arck = a[r].child[k]) != -1) {
					q.push(arck);
					int v = a[r].failure;
					while (a[v].child[k] == -1) v = a[v].failure;
					a[arck].failure = a[v].child[k];
					a[arck].match_par = a[v].child[k];
					while (a[arck].match_par != -1 && a[a[arck].match_par].match.empty())
						a[arck].match_par = a[a[arck].match_par].match_par;
				}
			}
		}
	}

	void aho_corasick(string &sentence, vector<string> &words,vvi &matches){
		matches.assign(sentence.length(), vi());
		int state = 0, ss = 0;
		for (int i = 0; i < sentence.length(); ++i, ss = state) {
			while (a[ss].child[mp(sentence[i])] == -1)
				ss = a[ss].failure;
			state = a[state].child[mp(sentence[i])]
			      = a[ss].child[mp(sentence[i])];
			for (ss = state; ss != -1; ss = a[ss].match_par)
				for (int w : a[ss].match)
					matches[i + 1 - words[w].length()].push_back(w);
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	string S;
	cin >> S;
	
	int W;
	cin >> W;
	vector<string> words(W, "");
	unordered_set<string> seen;
	for (int w = 0; w < W; ++w) {
		cin >> words[w];
		if (seen.find(words[w]) != seen.end()) {
			--w;
			--W;
			words.pop_back();
		} else seen.insert(words[w]);
	}
	
	vector<string> mwords(W, "");
	for (int i = 0; i < W; ++i) {
		mwords[i] = words[i];
		for (size_t j = 0; j < mwords[i].size(); ++j)
			if (mwords[i][j] >= 'A' && mwords[i][j] <= 'Z')
				mwords[i][j] += int('a' - 'A');
		for (size_t j = 0; j < mwords[i].size() / 2; ++j)
			swap(mwords[i][j], mwords[i][mwords[i].size()-1-j]);
	}
	
	AC_FSM<26, mfunc> fsm;
	fsm.construct_automaton(mwords);
	vvi matches;
	fsm.aho_corasick(S, mwords, matches);
	vii par(N + 1, {-1LL, -1LL});
	par[0] = {-1LL, -2LL};
	for (int i = 0; i < N; ++i) {
		if (par[i].second == -1LL) continue;
		
		for (int w : matches[i])
			if (par[i + mwords[w].length()].second == -1LL ) {
				par[i+mwords[w].length()] = {i, w};
			}
	}
	
	vi sol;
	int i = N;
	while (i > 0) {
		sol.push_back(par[i].second);
		i = par[i].first;	
	}
	
	bool sp = false;
	for (int i = int(sol.size()) - 1; i >= 0; --i) {
		if (sp) cout << " "; else sp = true;
		cout << words[sol[i]];
	}
	cout << endl;
	
	return 0;
}
