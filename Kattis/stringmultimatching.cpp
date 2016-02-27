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

int cmap(char c) { return int(c) - 32; }
constexpr int ASIZE = 96;


template <int ALPHABET_SIZE, int (*mp)(char)>
struct AC_FSM {
	struct Node {
		int child[ALPHABET_SIZE], failure = 0, match_parent = -1;
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
					a[arck].match_parent = a[v].child[k];
					while (a[arck].match_parent != -1 && a[a[arck].match_parent].match.empty())
						a[arck].match_parent = a[a[arck].match_parent].match_parent;
				}
			}
		}
	}

	void aho_corasick(string &sentence, vector<string> &words,vvi &matches){
		matches.assign(words.size(), vi());
		int state = 0, ss = 0;
		for (int i = 0; i < sentence.length(); ++i, ss = state) {
			while (a[ss].child[mp(sentence[i])] == -1)
				ss = a[ss].failure;
			state = a[state].child[mp(sentence[i])]
			      = a[ss].child[mp(sentence[i])];
			for (ss = state; ss != -1; ss = a[ss].match_parent)
				for (int w : a[ss].match)
					matches[w].push_back(i + 1- words[w].length());
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	while (cin >> N) {
		cin >> ws;
		vector<string> W(N, "");
		for (int i = 0; i < N; ++i)
			getline(cin, W[i]);
		
		AC_FSM<ASIZE, cmap> fsm;
		fsm.construct_automaton(W);
		
		string S;
		getline(cin, S);
		
		vvi matches;
		fsm.aho_corasick(S, W, matches);
		for (int i = 0; i < N; ++i) {
			bool sp = false;
			sort(matches[i].begin(), matches[i].end());
			for (int j : matches[i]) {
				if (sp) cout << " "; else sp = true;
				cout << j;
			}
			cout << '\n';
		}
		cout << flush;
	}
	
	return 0;
}
