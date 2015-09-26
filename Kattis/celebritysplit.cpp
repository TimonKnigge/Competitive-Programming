#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
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
	
	while (true) {
		int n;
		cin >> n;
		if (n == 0) break;
		
		int n1 = n / 2, n2 = n - n1;
		vector<ll> v1(n1, 0), v2(n2, 0);
		for (int i = 0; i < n1; ++i) cin >> v1[i];
		for (int i = 0; i < n2; ++i) cin >> v2[i];
		
		unordered_map<ll, ll> pos;
		int res = 1;
		for (int i = 0; i < n; ++i) res *= 3;
		pos.reserve(res);
		for (int msk = 0; msk < (1 << n1); ++msk) {
			// Everything turned off goes away
			ll away = 0LL, left = 0LL;
			for (int i = 0; i < n1; ++i) {
				if (((msk >> i)&1)==0) away += v1[i];
				else left += v1[i];
			}
			
			int msk2 = msk;
			do {
				ll right = 0LL;
				for (int i = 0; i < n1; ++i)
					if (((msk2 >> i)&1)==1) right += v1[i];
				// Insert abs(left - 2 * right)
				ll diff = abs(left - 2 * right);
				auto it = pos.find(diff);
				if (it == pos.end()) pos.insert({diff, away});
				else if (it->second > away) it->second = away;
				msk2 = (msk2 - 1) & msk;
			} while (msk2 != msk);
		}
//		cout << n1 << endl;
//		for (auto it : pos) cout << it.first << ' ' << it.second <<endl;
		ll best = LLINF;
		for (int msk = 0; msk < (1 << n2); ++msk) {
			// Everything turned off goes away
			ll away = 0LL, left = 0LL;
			for (int i = 0; i < n2; ++i) {
				if (((msk >> i)&1)==0) away += v2[i];
				else left += v2[i];
			}
			int msk2 = msk;
			do {
				ll right = 0LL;
				for (int i = 0; i < n2; ++i)
					if (((msk2>>i)&1)==1) right += v2[i];
				ll diff = abs(left - 2 * right);
				auto it = pos.find(diff);
				if (it != pos.end()) {
					ll rm = away + it->second;
					if (rm < best) best = rm;
				}
				msk2 = (msk2 - 1) & msk;
			} while (msk2 != msk);
		}
		
		cout << best << endl;
	}
	
	return 0;
}
