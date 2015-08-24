#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

// suffixarray
struct S { int l, r, p; };
bool operator<(const S &lhs, const S &rhs) { 
	return lhs.l != rhs.l ? lhs.l < rhs.l : lhs.r < rhs.r; 
}
bool operator==(const S &lhs, const S &rhs) {
	return lhs.l == rhs.l && lhs.r == rhs.r;
}

struct SuffixArray {
	string s;
	int n;
	vvi P;
	SuffixArray(string &_s) : s(_s), n(_s.length()) { construct(); }
	void construct() {
		vector<S> L(n, {0, 0, 0});
		P.push_back(vi(n, 0));
		for (int i = 0; i < n; ++i) P[0][i] = int(s[i]);
		for (int k = 1, cnt = 1; cnt / 2 < n; ++k, cnt *= 2) {
			P.push_back(vi(n, 0));
			for (int i = 0; i < n; ++i)
				L[i] = { P[k - 1][i], i + cnt < n 
					? P[k - 1][i + cnt] : -1000, i};
			sort(L.begin(), L.end());
			for (int i = 0; i < n; ++i)
				P[k][L[i].p] = (i > 0 && L[i] == L[i - 1]
				? P[k][L[i - 1].p] : i);
		}
	}
	vi &get_array() { return P.back(); }
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int k = P.size() - 1; k >= 0 && x < n && y < n; --k)
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
			}
		return ret;
	}
};
// -suffixarray

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	while (true) {
		cin >> n;
		if (n == 0) break;
		

		map<int, int> mp;
		string s, t;
		cin >> s;
		mp.insert({s.length(), 0});
		for (int i = 1; i < n; ++i) {
			cin >> t;
			s = s + char(int('z') + i) + t;
			mp.insert({s.length(), i});
		}

		SuffixArray sa(s);
		vector<int> inv(s.length(), 0), &arr = sa.get_array();
		for (int i = 0; i < arr.size(); ++i)
			inv[arr[i]] = i;

		vector<int> cm;
		int L = 0;
		map<int, int> diff;
		int l = 0, r = 0; // [l, r]
		for (; r < s.length(); ++r) {
//			cerr << "[" << l << ", " << r << "]"<<endl;
			// add r
			int id = mp.lower_bound(inv[r])->second;
			if (diff.find(id) == diff.end())
				diff.insert({id, 1});
			else
				diff[id]++;
			
			// while there are enough thingies, record and remove l
			while (diff.size() > n / 2) {
				int lcp = sa.lcp(inv[l], inv[r]);
				if (lcp > L) {
					L = lcp;
					cm.clear();
					cm.push_back(inv[l]);
				} else if (lcp == L && L != 0)
					cm.push_back(inv[l]);
				// remove l
				int id2 = mp.lower_bound(inv[l])->second;
				auto it = diff.find(id2);
				if (it->second > 1) it->second--;
				else diff.erase(it);
				l++;	
			}
		}
		
		if (cm.size() == 0) cout << "?" << endl;
		else {
			string last = " ", nw = "";
			for (int i = 0; i < cm.size(); ++i) {
				nw = "";
				for (int j = 0; j < L; ++j)
					nw = nw + s[cm[i] + j];
				if (nw == last) continue;
				last = nw;
				cout << nw << '\n';
			}
			cout << endl;
		}
	}
	
	return 0;
}

