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

int arr[1000000];

int main() {
	
	int N, K;
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &arr[i]);
	}
	
	sort(arr, arr + N);
	
	int count = 0;
	int ans = -1;
	for (int i = 0; i < N; ++i) {
		if (i > 0 && arr[i] != arr[i - 1]) {
			if (count % K != 0) {
				ans = arr[i - 1];
				break;
			}
			count = 1;
		} else count++;
	}
	if (ans == -1) ans = arr[N - 1];
	cout << ans << endl;
	
	return 0;
}
