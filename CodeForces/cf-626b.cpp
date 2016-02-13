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
using iii = pair<int, ii>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int gtype(char c) {
	if (c == 'B') return 0;
	if (c == 'G') return 1;
	return 2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	string S;
	cin >> N >> S;
	
	int C[3] = {0, 0, 0};
	for (int i = 0; i < N; ++i)
		C[gtype(S[i])]++;
	
	
	queue<iii> q;
	q.push({C[0], {C[1], C[2]}});
	set<iii> seen;
	while (!q.empty()) {
		iii t = q.front();
		q.pop();
		if (seen.find(t) != seen.end()) continue;
		seen.insert(t);
		
		if (t.first > 1)
			q.push({t.first-1, t.second});
		if (t.second.first > 0 && t.second.second > 0)
			q.push({t.first+1, {t.second.first-1,t.second.second-1}});
		
		if (t.second.first > 1)
			q.push({t.first, {t.second.first-1, t.second.second}});
		if (t.first > 0 && t.second.second > 0)
			q.push({t.first-1, {t.second.first+1,t.second.second-1}});
		
		if (t.second.second > 1)
			q.push({t.first, {t.second.first,t.second.second-1}});
		if (t.second.first > 0 && t.first> 0)
			q.push({t.first-1, {t.second.first-1,t.second.second+1}});
		
	}
	if (seen.find({1, {0, 0}}) != seen.end()) cout << 'B';
	if (seen.find({0, {1, 0}}) != seen.end()) cout << 'G';
	if (seen.find({0, {0, 1}}) != seen.end()) cout << 'R';
	cout << endl;
	
	return 0;
}
