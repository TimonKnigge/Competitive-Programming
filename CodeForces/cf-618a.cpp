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
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	
	int n;
	cin >> n;
	
	vi res(1, 1);
	for (int i = 1; i < n; ++i) {
		res.push_back(1);
		while (res.size() > 1 && res[int(res.size())-2] == res[int(res.size())-1]) {
			res.pop_back();
			res.back()++;
		}
	}
	
	for (int i = 0; i < res.size(); ++i)
		cout << res[i] << " \n"[i == int(res.size()) - 1];
	
	return 0;
}
