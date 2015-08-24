#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int ALPH = 26;
inline int mp(char c) { return c - 'a'; }

struct Node {
	Node *ch[ALPH];
	int isleaf = -1;
	int d = 0, sz = 0;
	vector<int> ind;
	Node() {
		for (int i = 0; i < ALPH; ++i) ch[i] = NULL;
	}
	void insert(string &s, int id, int i = 0) {
		ind.push_back(id);
		sz++;
		if (i == s.length()) isleaf = id;
		else {
			int v = mp(s[i]);
			if (ch[v] == NULL) {
				ch[v] = new Node();
				ch[v]->d = d + 1;
			}
			ch[v]->insert(s, id, i + 1);
		}
	}
	
	ll cost(string &s, int LB, int i = 0) {
//		cout << "Cost @ depth " << d << " length " << i << " encapsulating " << sz << " descendants" << endl;
		if (i == s.length()) {
			ll ret = 0LL;
			int c = upper_bound(ind.begin(), ind.end(), LB) - ind.begin();
			ret += c * (d + 1);
			return ret;
		}
		else {
			int v = mp(s[i]);
			ll ret = (isleaf != -1 && isleaf <= LB ? d + 1 : 0);
			for (int j = 0; j < ALPH; ++j) {
				if (ch[j] == NULL) continue;
				if (j == v) {
					ret += ch[j]->cost(s, LB, i + 1);
				} else {
					ret += ch[j]->basecost(LB);
				}
			}
//			cout << i << " is returning " << ret << endl;
			return ret;
		}
	}

	ll basecost(int LB) {
		int c = upper_bound(ind.begin(), ind.end(), LB) - ind.begin();
		return c * d;
	}

	int contains(string &s, int i = 0) {
		if (i == s.length()) return isleaf;
		else {
			int v = mp(s[i]);
			if (ch[v] == NULL) return -1;
			else return ch[v]->contains(s, i + 1);
		}
	}
	
	void cleanup() {
		for (int i = 0; i < ALPH; ++i)
			if (ch[i] != NULL) {
				ch[i]->cleanup();
				delete ch[i];
			}
	}
};

int main () {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	Node root;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		root.insert(s, i);
	}
	
	int q;
	cin >> q;
	for (int i = 0; i < q; ++i) {
		string t;
		cin >> t;

		int id = root.contains(t);
		if (id == -1) id = n + 2;

		cout << root.cost(t, id) << '\n';
	}
	cout << flush;
	
	root.cleanup();
	
	return 0;
}
