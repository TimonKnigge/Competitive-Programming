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
#include <unordered_map>

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

int toid(string &S, unordered_map<string, int> &mp) {
	auto it = mp.find(S);
	if (it != mp.end()) return it->second;
	int ret = mp.size();
	mp.insert({S, ret});
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	cin >> N;
	
	unordered_map<string, int> hostmap, pathmap;
	vector<string> hostname;
	vector<set<int> > idlst;
	for (int i = 0; i < N; ++i) {
		string Q, P = "";
		cin >> Q;
		Q = Q.substr(7);
		int p = 0;
		while (p < Q.size() && Q[p] != '/') ++p;
		if (p < Q.size()) {
			P = Q.substr(p);
			Q = Q.substr(0, p);
		}
		int hid = toid(Q, hostmap);
		int pid = toid(P, pathmap);
		
		if (hid >= hostname.size()) {
			hostname.push_back(Q);
			idlst.push_back(set<int>());
		}
		idlst[hid].insert(pid);
	}
	
	vvi hostlist;
	unordered_map<string, int> normalform;
	for (int i = 0; i < idlst.size(); ++i) {
		string nf = "";
		for (auto it = idlst[i].begin(); it != idlst[i].end(); ++it) {
			nf = nf + to_string(*it) + '_';
		}
		int id = toid(nf, normalform);
		if (id >= hostlist.size())
			hostlist.push_back(vi());
		hostlist[id].push_back(i);
	}
	
	int D = 0;
	for (size_t i = 0; i < hostlist.size(); ++i)
		if (hostlist[i].size() > 1) ++D;
	
	cout << D << endl;
	for (size_t i = 0; i < hostlist.size(); ++i) {
		if (hostlist[i].size() <= 1) continue;
		for (size_t j = 0; j < hostlist[i].size(); ++j)
			cout << "http://" << hostname[hostlist[i][j]]
				<< " \n"[j + 1 == hostlist[i].size()];
	}
	
	return 0;
}
