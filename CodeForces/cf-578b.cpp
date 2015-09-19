#include <iostream> 
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
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k, _x;
	cin >> n >> k >> _x;
	int MX = 45;
	vector<vector<bool> > bw(n, vector<bool>(MX, false));
	vector<int> bitval(MX, 0);
	vector<ll> av(n, 0);
	for (int i = 0; i < n; ++i) {
		ll a;
		cin >> a;
		av[i] = a;
		for (int j = 0; j < MX; ++j)
			if (((1LL << j)&a) != 0){
				bw[i][j] = true;
				bitval[j]++;
			}
	}
	
	ll x = 1;
	for (int i = 0; i < k; ++i) x *= _x;
	
	ll maxv = 0LL; int maxi = 0;
		for (int i = 0; i < n; ++i) {
			ll tmp = 0LL;
			for (int j = 0; j < MX; ++j) {
				if (bitval[j] - bw[i][j] > 0) tmp |= (1LL << j);
			}
			if ((tmp | (av[i] * x)) > maxv) {
				maxv = (tmp | (av[i] * x));
				maxi = i;
			}
		}
		
		for (int j = 0; j < MX; ++j) {
			if (bw[maxi][j]) { bitval[j]--; bw[maxi][j] = false;}
		}
		av[maxi] *= x;
		for (int j = 0; j < MX; ++j) {
			if (((1LL << j) & av[maxi]) != 0) {
				bitval[j]++;
				bw[maxi][j] = true;
			}
		}
	maxv = 0LL;
	for (int i = 0; i < n; ++i)
		maxv |= av[i];
	cout << maxv << endl;
	
	return 0;
}
