#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <math.h>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef long long ll;

bool precedes[26][26];
vector<char> ordering;
vector<bool> marked(26, false);
bool cyc = false;

// CYCLE DETECTION
void dfs(int u, int p, int s) {
	if (marked[u]) {
		if (u == s) cyc = true;
		return;
	}
	marked[u] = true;
	
	for (int v = 0; v < 26; ++v) {
		if (precedes[u][v])
			dfs(v, u, s);
	}
}

bool find_cycle() {
	for (int s = 0; s < 26; ++s) {
		fill(marked.begin(), marked.end(), false);
		dfs(s, -1, s);
		if (cyc) return true;
	}
	return false;
}
// -CYCLE DETECTION

void toposort(int u) {
	if (marked[u]) return;
	marked[u] = true;
	for (int v = 0; v < 26; ++v) {
		if (precedes[u][v] && !marked[v])
			toposort(v);
	}
	ordering.push_back((char)('a' + u));
}

int main(){
	int n;
	cin >> n;

	// Read input
	vector<string> words(n);
	int M = 0;
	for (int i = 0; i < n; ++i) {
		cin >> words[i];
		if (M < words[i].length()) {
			M = words[i].length();
		}
	}
	
	// Process groups of words that conflict, start with all words
	queue<pair<int, vi> > toProcess;
	vector<int> init(n);
	for (int i = 0; i < n; ++i) init[i] = i;
	toProcess.push(pair<int, vi>(0, init));
	bool impossible = false;
	while (!toProcess.empty() && !impossible) {
		// Retrieve words
		pair<int, vi> front = toProcess.front(); toProcess.pop();
		vi todo = front.second, t; int d = front.first;
		vvi confl(26);
		sort(todo.begin(), todo.end());
		for (int i = 0; i < todo.size(); ++i)
			if (i == 0 || todo[i - 1] != todo[i])
				t.push_back(todo[i]);

		// Compare all words, save the ones that still conflict
		for (int w1 = 0; w1 < t.size(); ++w1) {
			for (int w2 = w1 + 1; w2 < t.size(); ++w2) {
				if (t[w1] == t[w2]) continue;
				if (words[t[w2]].length() <= d && words[t[w1]].length() > d) {
					impossible = true;
					break;
				}
				else if (words[t[w1]].length() <= d || words[t[w2]].length() <= d) {
					continue;
				}
				char lc = words[t[w1]].at(d), rc = words[t[w2]].at(d);

				if (lc == rc) {
					confl[lc - 'a'].push_back(t[w1]);
					confl[rc - 'a'].push_back(t[w2]);
				}
				else {
					precedes[lc - 'a'][rc - 'a'] = true;
				}
			}
		}

		// Enqueue conflicts
		for (int i = 0; i < 26; ++i) {
			if (confl[i].size() > 0)
				toProcess.push(pair<int, vi>(d + 1, confl[i]));
		}
	}

	// If there is a cycle or a different sort of conflict: impossible
	bool cycle = find_cycle();
	if (cycle || impossible)
		cout << "Impossible" << endl;
	else {
		// Generate a solution
		fill(marked.begin(), marked.end(), false);
		for (int d = 0; d < 26; ++d) {
			toposort(d);
		}
		for (int d = 25; d >= 0; --d)
			cout << ordering[d];
		cout << endl;
	}

	return 0;
}