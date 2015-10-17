#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Length only
template<class T>
int longest_increasing_subsequence(vector<T> &a) {
	set<T> st;
	typename set<T>::iterator it;
	for (int i = 0; i < a.size(); ++i) {
		it = st.lower_bound(a[i]);
		if (it != st.end()) st.erase(it);
		st.insert(a[i]);
	}
	return st.size();
}

int main() {
	int N, M, D;
	scanf("%d %d %d", &N, &M, &D);
	
	int id = 0;
	unordered_map<string, int> idmap;
	vector<vector<int> > e;
	vector<int> indeg;
	for (int i = 0; i < M; ++i) {
		string sA, sB;
		cin >> sA >> sB;
		int A, B;
		auto it = idmap.find(sA);
		if (it == idmap.end()) {
			idmap.insert({sA, id});
			A = id;
			id++;
			e.push_back(vector<int>());
			indeg.push_back(0);
		} else A = it->second;
		it = idmap.find(sB);
		if (it == idmap.end()) {
			idmap.insert({sB, id});
			B = id;
			id++;
			e.push_back(vector<int>());
			indeg.push_back(0);
		} else B = it->second;
		
		indeg[B]++;
		e[A].push_back(B);
	}
	
	// Toposort
	queue<int> q;
	vector<int> topo;
	for (int i = 0; i < indeg.size(); ++i)
		if (indeg[i] == 0) q.push(i);
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		topo.push_back(u);
		for (int v : e[u]) {
			indeg[v]--;
			if (indeg[v] == 0) q.push(v);
		}
	}
	
	map<int, int> mapmap;
	for (int i = 0; i < topo.size(); ++i) {
		mapmap.insert({topo[i], i});
	}
	
	vector<int> rank;
	for (int i = 0; i < N; ++i) {
		string sC;
		cin >> sC;
		auto it = idmap.find(sC);
		if (it == idmap.end())
			continue;
		auto it2 = mapmap.find(it->second);
		rank.push_back(it2->second);
	}
	
	printf("%d\n", 2 * (N - longest_increasing_subsequence(rank)));
	
	return 0;
}
