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
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int gcd(int a, int b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

int main() {
	
	int N;
	scanf("%d", &N);
	map<int, int> mp;
	for (int i = 0; i < N * N; ++i) {
		int AI;
		scanf("%d", &AI);
		auto it = mp.find(AI);
		if (it == mp.end()) mp.insert({AI, 1});
		else it->second++;
	}
	
	vi el;
	while (mp.size() > 0) {
		auto it = mp.rbegin();
		int v = it->first;
		if (it->second == 1) mp.erase(v);
		else it->second--;
		
		for (int i = 0; i < el.size(); ++i) {
			int ggd = gcd(el[i], v);
			auto it2 = mp.find(ggd);
			if (it2->second == 2) mp.erase(ggd);
			else it2->second -= 2;
		}
		
		el.push_back(v);
	}
	
	printf("%d", el[0]);
	for (int i = 1; i < el.size(); ++i) printf(" %d", el[i]);
	printf("\n");
	
	return 0;
}
