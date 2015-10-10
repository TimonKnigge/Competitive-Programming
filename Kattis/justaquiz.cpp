#include <iostream> 
#include <sstream>
#include <iomanip>
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
#include <unordered_map>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;
using ld = long double;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

struct node {
	bool leaf = false;
	int children = 0;
	map<int, int> ans;
	map<int, int> ch;
};
vector<node> tree(100000, node());
int OPEN = 0;

void insert(int i, vi &q, int p, int aans) {
	node &n = tree[i];
	auto it = n.ans.find(aans);
	if (it != n.ans.end()) it->second++;
	else n.ans.insert({aans, 1});
	n.children++;
	if (p == q.size()) {
		n.leaf = true;
		return;
	}
	auto it2 = n.ch.find(q[p]);
	if (it2 != n.ch.end()) {
		insert(it2->second, q, p + 1, aans);
	} else {
		OPEN++;
		n.ch.insert({q[p], OPEN - 1});
		insert(OPEN - 1, q, p + 1, aans);
	}
}

ld dfs(int i, int time, vector<ld> &best) {
	if (time < 1) return 0.0;
	// Best we can get in each child
	node &n = tree[i];
	ld sum = 0.0;
	for (auto it : n.ch) {
		node &nc = tree[it.second];
		sum += dfs(it.second, time - 1, best) * (nc.children / ld(n.children));
	}
	
	// What if we guess now?
	ld selfbest = 0.0, thistime;
	for (auto it : n.ans) {
		thistime = best[time - 1];
		thistime += (it.second / ld(n.children));
		if (thistime > selfbest) selfbest = thistime;
	}
	
	if (selfbest > sum) sum = selfbest;
	return sum;
}

void calc(int time, vector<ld> &best) {
	// Start calculating from 0
	best[time] = dfs(0, time, best);
}

void extract_words(string &sent, vector<string> &words) {
	string word;
	stringstream ss;
	ss << sent;
	while (ss >> word) {
		words.push_back(word);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t, n;
	cin >> t >> n >> ws;
	
	unordered_map<string, int> mp;
	unordered_map<string, int> mpans;
	int id = 0, aid = 0;
	vvi q(n, vi()); vi ans(n, 0);
	for (int i = 0; i < n; ++i) {
		string sent;
		getline(cin, sent);
		vector<string> words;
		
		extract_words(sent, words);
		
		for (int j = 0; j < int(words.size()) - 1; ++j) {
			string &word = words[j];
			auto it = mp.find(word);
			if (it != mp.end()) {
				q[i].push_back(it->second);
			} else { 
				q[i].push_back(id);
				mp.insert({word, id});
				id++;
			}
		}
		string &answer = words.back();
		auto it = mpans.find(answer);
		if (it != mpans.end())
			ans[i] = it->second;
		else {
			ans[i] = aid;
			mpans.insert({answer, aid});
			aid++;
		}
	}
	
	// Build the tree
	OPEN++;
	tree.push_back(node());
	for (int i = 0; i < n; ++i) {
		insert(0, q[i], 0, ans[i]);
	}
	
	vector<ld> best(t + 1, 0.0);
	for (int time = 1; time <= t; ++time) {
		calc(time, best);
	}
	
	printf("%.7lf\n", double(best[t]));
	
	return 0;
}
