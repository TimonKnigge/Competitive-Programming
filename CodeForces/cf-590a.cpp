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

int main() {
	
	int N;
	scanf("%d", &N);
	vector<int> v(N, 0);
	for (int i = 0; i < N; ++i)
		scanf("%d", &v[i]);
	
	vb stable(N, true);
	stable[0] = stable[N - 1] = true;
	for (int i = 1; i < N - 1; ++i)
		if (v[i] != v[i - 1] && v[i] != v[i + 1])
			stable[i] = false;
	
	int ls = 0;
	int maxtime = 0;
	for (int i = 1; i < N; ++i) {
		if (stable[i]) {
			int lt = v[ls], rt = v[i];
			int j = 1;
			while (!stable[ls + j] || !stable[i - j]) {
				v[ls + j] = lt;	
				v[i - j] = rt;
				stable[ls + j] = true;
				stable[i - j] = true;
				j++;
			}
			
			maxtime = max(maxtime, (i - ls) / 2);
			
			ls = i;
		}
	}
	
	cout << maxtime << endl;
	for (int i = 0; i < N; ++i)
		cout << v[i] << " \n"[i == N - 1];
	
	return 0;
}
